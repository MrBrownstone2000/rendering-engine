#include "pch.hpp"
#include "gltfImporter.hpp"

#include <fastgltf/parser.hpp>
#include <fastgltf/types.hpp>

namespace engine
{
    namespace ImporterGltf
    {
        Mesh ImportText(const std::filesystem::path& path)
        {
            fastgltf::Parser parser(fastgltf::Extensions::KHR_lights_punctual);
            fastgltf::GltfDataBuffer data;
            data.loadFromFile(path);

            auto asset = parser.loadGLTF(&data, path.parent_path(), fastgltf::Options::None);
            if (auto error = asset.error(); error != fastgltf::Error::None)
            {
                engineLog.error("GLTF Parsing Failed...").watch(int(error));
                // TODO: print error message
            }
            
            // TODO: use accessors to load mesh hierarchy ?


            return Mesh();
        }

        Mesh ImportBinary(const std::filesystem::path& path)
        {
            return Mesh();
        }
    }
}
