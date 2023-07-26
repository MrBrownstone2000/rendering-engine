#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "../gfx/vertexArray.hpp"
#include "../util/types.hpp"

namespace engine::renderer
{
    struct Vertex
    {
        // float position[3];
        // float normal[3];
        // float texCoords[2];
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
        Mesh(float* vertices, size_t sv, uint32_t* indices, size_t si);

        std::shared_ptr<const renderer::VertexArray> getVAO() const { return m_vao; }

    private:
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        std::shared_ptr<renderer::VertexArray> m_vao;
    };
}

#endif
