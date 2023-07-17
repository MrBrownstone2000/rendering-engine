#include "pch.hpp"
#include "vertexBuffer.hpp"

namespace engine::renderer
{
    VertexBuffer::VertexBuffer(float* vertices, uint size)
    {
        glCreateBuffers(1, &m_id);
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
        m_layout = std::move(rhs.m_layout);
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs)
    {
        glDeleteBuffers(1, &m_id);
        m_id = rhs.m_id;
        rhs.m_id = 0;
        m_layout = std::move(rhs.m_layout);
        return *this;
    }

    void VertexBuffer::setLayout(const BufferLayout& layout)
    {
        m_layout = layout;
    }

    const BufferLayout& VertexBuffer::getLayout() const
    {
        return m_layout;
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
