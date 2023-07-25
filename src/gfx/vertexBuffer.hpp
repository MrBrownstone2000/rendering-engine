#ifndef __VERTEXBUFFER_HPP__
#define __VERTEXBUFFER_HPP__

#include "bufferLayout.hpp"
#include "../util/types.hpp"

namespace engine::renderer
{
    class VertexBuffer
    {
        public:
            VertexBuffer() : m_id(0) {}
            VertexBuffer(float* vertices, uint size);
            ~VertexBuffer();

            VertexBuffer(const VertexBuffer& rhs) = delete;
            VertexBuffer(VertexBuffer&& rhs);
            VertexBuffer& operator=(const VertexBuffer& rhs) = delete;
            VertexBuffer& operator=(VertexBuffer&& rhs);

            void setLayout(const BufferLayout& layout);
            const BufferLayout& getLayout() const;

            void bind() const;
            void unbind() const;

        private:
            uint32_t m_id;
            BufferLayout m_layout;
    };
};

#endif
