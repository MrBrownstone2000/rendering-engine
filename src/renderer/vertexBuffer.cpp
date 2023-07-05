#include "pch.hpp"
#include "vertexBuffer.hpp"

namespace engine::renderer
{
    VertexBuffer::VertexBuffer(float* vertices, uint size)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& rhs)
    {
        m_id = rhs.m_id;
        rhs.m_id = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs)
    {
        glDeleteBuffers(1, &m_id);
        m_id = rhs.m_id;
        rhs.m_id = 0;
        return *this;
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
