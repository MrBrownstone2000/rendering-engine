#ifndef __VERTEXARRAY_HPP__
#define __VERTEXARRAY_HPP__

#include "indexBuffer.hpp"
#include "vertexBuffer.hpp"
#include "../util/types.hpp"

#include <memory>

namespace engine
{
    class VertexArray
    {
        public:
            VertexArray();
            VertexArray(VertexBuffer&& vbo, IndexBuffer&& ebo);
            VertexArray(const std::shared_ptr<VertexBuffer>& vbo, const std::shared_ptr<IndexBuffer>& ebo);
            ~VertexArray();

            VertexArray(const VertexArray& rhs) = delete;
            VertexArray(VertexArray&& rhs);
            VertexArray& operator=(const VertexArray& rhs) = delete;
            VertexArray& operator=(VertexArray&& rhs);

            void attachVertexBuffer(VertexBuffer&& vbo);
            void attachVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo);
            void attachIndexBuffer(IndexBuffer&& vbo);
            void attachIndexBuffer(const std::shared_ptr<IndexBuffer>& vbo);
            
            void bind() const;
            void unbind() const;

            uint getCount() const { return m_ebo->getCount(); }

        private:
            void setVertexBufferLayout();

        private:
            uint32_t m_id;

            std::shared_ptr<VertexBuffer> m_vbo;
            std::shared_ptr<IndexBuffer> m_ebo;
    };
}

#endif
