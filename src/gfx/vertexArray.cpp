#include "pch.hpp"
#include "vertexArray.hpp"

#include <GL/glew.h>

namespace engine
{
    VertexArray::VertexArray()
    {
        m_id = 0;
        // Can't do that: window needs to be created for glew to  be initialized
        // => If create buffers here, glew is not initialized !!!
        
        // glCreateVertexArrays(1, &m_id);
        // glBindVertexArray(m_id);
    }

    VertexArray::VertexArray(VertexBuffer&& vbo, IndexBuffer&& ebo)
        : m_vbo(std::make_shared<VertexBuffer>(std::move(vbo))),
        m_ebo(std::make_shared<IndexBuffer>(std::move(ebo)))
    {
        glCreateVertexArrays(1, &m_id);
        glBindVertexArray(m_id);

        m_vbo->bind();
        setVertexBufferLayout();

        m_ebo->bind();
    }

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vbo, const std::shared_ptr<IndexBuffer>& ebo)
        : m_vbo(vbo), m_ebo(ebo)
    {
        glCreateVertexArrays(1, &m_id);
        glBindVertexArray(m_id);

        setVertexBufferLayout();
        m_ebo->bind();
    }

    void VertexArray::attachVertexBuffer(VertexBuffer&& vbo)
    {
        if (!m_id)
        {
            glCreateVertexArrays(1, &m_id);
            glBindVertexArray(m_id);
        }
        m_vbo = std::make_shared<VertexBuffer>(std::move(vbo));
        setVertexBufferLayout();
    }

    void VertexArray::attachVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
    {
        if (!m_id)
        {
            glCreateVertexArrays(1, &m_id);
            glBindVertexArray(m_id);
        }
        m_vbo = vbo;
        setVertexBufferLayout();
    }

    void VertexArray::setVertexBufferLayout()
    {
        m_vbo->bind();
        int i = 0;
        const auto& layout = m_vbo->getLayout();
        for (const auto& elt : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, 
                    elt.getCount(), 
                    elt.getGLBaseType(), 
                    elt.isNormalized() ? GL_TRUE : GL_FALSE, 
                    layout.getStride(), 
                    reinterpret_cast<void*>(elt.m_offset)
                );
            ++i;
        }
    }

    void VertexArray::attachIndexBuffer(IndexBuffer&& ebo)
    {
        if (!m_id)
        {
            glCreateVertexArrays(1, &m_id);
            glBindVertexArray(m_id);
        }
        m_ebo = std::make_shared<IndexBuffer>(std::move(ebo));
        m_ebo->bind();
    }

    void VertexArray::attachIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo)
    {
        if (!m_id)
        {
            glCreateVertexArrays(1, &m_id);
            glBindVertexArray(m_id);
        }
        m_ebo = ebo;
        m_ebo->bind();
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    VertexArray::VertexArray(VertexArray&& rhs)
    {
        m_vbo = std::move(rhs.m_vbo);
        m_ebo = std::move(rhs.m_ebo);
        m_id = rhs.m_id;
        rhs.m_id = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& rhs)
    {
        glDeleteVertexArrays(1, &m_id);

        m_vbo = std::move(rhs.m_vbo);
        m_ebo = std::move(rhs.m_ebo);
        m_id = rhs.m_id;
        rhs.m_id = 0;

        return *this;
    }
    
    void VertexArray::bind() const
    {
        glBindVertexArray(m_id);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }
}
