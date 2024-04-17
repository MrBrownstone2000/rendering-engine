#include "pch.hpp"
#include "assets/gltfImporter.hpp"

#include <fastgltf/glm_element_traits.hpp>
#include <fastgltf/parser.hpp>
#include <fastgltf/tools.hpp>
#include <fastgltf/types.hpp>

namespace engine
{
    namespace ImporterGltf
    {
        Model Import(const std::filesystem::path& path)
        {
            constexpr auto extensions = fastgltf::Extensions::KHR_lights_punctual;
            fastgltf::Parser parser(extensions);

            fastgltf::GltfDataBuffer data;
            data.loadFromFile(path);

            constexpr auto options = fastgltf::Options::DontRequireValidAssetMember | 
                fastgltf::Options::AllowDouble | 
                fastgltf::Options::LoadGLBBuffers | 
                fastgltf::Options::LoadExternalBuffers;

            fastgltf::Asset asset;

            auto type = fastgltf::determineGltfFileType(&data);
            if (type == fastgltf::GltfType::glTF) {
                auto load = parser.loadGLTF(&data, path.parent_path(), options);
                if (load) {
                    asset = std::move(load.get());
                } else {
                    engineLog.error("Failed to load glTF: " + std::string(fastgltf::getErrorMessage(load.error())));
                }
            } else if (type == fastgltf::GltfType::GLB) {
                auto load = parser.loadBinaryGLTF(&data, path.parent_path(), options);
                if (load) {
                    asset = std::move(load.get());
                } else {
                    engineLog.error("Failed to load glTF: " + std::string(fastgltf::getErrorMessage(load.error())));
                }
            } else {
                engineLog.error("Failed to determine glTF container");
            }

            engineLog.info("GLTF File loaded");
            
            // TODO: use accessors to load mesh hierarchy
            // https://fastgltf.readthedocs.io/latest/tools.html
            // https://vkguide.dev/docs/new_chapter_5/gltf_nodes/
            
            std::vector<Mesh> meshes;

            // GLTF Mesh: attached to node (and have model matrix)
            for (fastgltf::Mesh& mesh : asset.meshes) 
            {
                // GLTF Primitive: used to separate different materials in a GLTF mesh
                for (fastgltf::Primitive& p : mesh.primitives) 
                {
                    std::vector<Vertex> vertices;
                    std::vector<uint32_t> indices;

                    // load indexes
                    {
                        fastgltf::Accessor& indexaccessor = asset.accessors[p.indicesAccessor.value()];
                        indices.reserve(indexaccessor.count);

                        fastgltf::iterateAccessor<std::uint32_t>(asset, indexaccessor,
                            [&](std::uint32_t idx) {
                                indices.push_back(idx);
                            });
                    }

                    // load vertex positions
                    {
                        fastgltf::Accessor& posAccessor = asset.accessors[p.findAttribute("POSITION")->second];
                        vertices.resize(posAccessor.count);

                        fastgltf::iterateAccessorWithIndex<glm::vec3>(asset, posAccessor,
                            [&](glm::vec3 v, size_t index) {
                                Vertex newVtx;
                                newVtx.position = v;
                                newVtx.normal = glm::vec3(1, 0, 0);
                                newVtx.texCoords = glm::vec2(0, 0);
                                vertices[index] = newVtx;
                            });
                    }

                    // load vertex normals
                    auto normals = p.findAttribute("NORMAL");
                    if (normals != p.attributes.end()) {

                        fastgltf::iterateAccessorWithIndex<glm::vec3>(asset, asset.accessors[(*normals).second],
                            [&](glm::vec3 n, size_t index) {
                                vertices[index].normal = n;
                            });
                    }
                    else
                        engineLog.warn("Mesh Primitive has no normal !");

                    // load UVs
                    auto uv = p.findAttribute("TEXCOORD_0");
                    if (uv != p.attributes.end()) {

                        fastgltf::iterateAccessorWithIndex<glm::vec2>(asset, asset.accessors[(*uv).second],
                            [&](glm::vec2 uv, size_t index) {
                                vertices[index].texCoords = uv;
                            });
                    }
                    else
                        engineLog.warn("Mesh Primitive has no texture coordinates !");

                    meshes.emplace_back(std::move(vertices), std::move(indices));
                }
            }

            engineLog.info(std::to_string(meshes.size()) + " meshes loaded");

            return Model(std::move(meshes));
        }
    }
}
