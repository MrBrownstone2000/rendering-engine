#include "pch.hpp"
#include "indexBuffer.hpp"

#include <GL/glew.h>

namespace engine
{
    IndexBuffer::IndexBuffer(uint* indices, uint count)
        : m_count(count)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& rhs)
    {
        m_id = rhs.m_id;
        rhs.m_id = 0;
        m_count = rhs.m_count;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs)
    {
        glDeleteBuffers(1, &m_id);
        m_id = rhs.m_id;
        rhs.m_id = 0;
        m_count = rhs.m_count;
        return *this;
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint IndexBuffer::getCount() const
    {
        return m_count;
    }
}
