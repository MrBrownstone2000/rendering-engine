#include "pch.hpp"
#include "mesh.hpp"

namespace engine::renderer
{
    Mesh::Mesh()
        : m_vao(std::make_shared<VertexArray>())
    {
    }

    Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices)),
        m_vao(std::make_shared<VertexArray>())
    {
        std::shared_ptr<VertexBuffer> vbo = 
            std::make_shared<VertexBuffer>(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
        vbo->setLayout({
            { ShaderDataType::float3, "position" },
            { ShaderDataType::float3, "normal" },
            { ShaderDataType::float2, "texCoords" },
        });
        m_vao->attachVertexBuffer(vbo);

        m_vao->attachIndexBuffer(IndexBuffer(m_indices.data(), 6));
    }

    Mesh::Mesh(float* vertices, size_t sv, uint32_t* indices, size_t si)
        : m_vao(std::make_shared<VertexArray>())
    {
        std::shared_ptr<VertexBuffer> vbo = 
            std::make_shared<VertexBuffer>(vertices, sv);
        vbo->setLayout({
            { ShaderDataType::float3, "position" },
            { ShaderDataType::float3, "normal" },
            { ShaderDataType::float2, "texCoords" },
        });
        m_vao->attachVertexBuffer(vbo);

        m_vao->attachIndexBuffer(IndexBuffer(indices, si));
    }
}
