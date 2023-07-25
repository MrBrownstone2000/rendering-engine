#ifndef __INDEXBUFFER_HPP__
#define __INDEXBUFFER_HPP__

#include "../util/types.hpp"

namespace engine::renderer
{
    class IndexBuffer
    {
        public:
            IndexBuffer() : m_id(0) {}
            IndexBuffer(uint* indices, uint count);
            ~IndexBuffer();

            IndexBuffer(const IndexBuffer& rhs) = delete;
            IndexBuffer(IndexBuffer&& rhs);
            IndexBuffer& operator=(const IndexBuffer& rhs) = delete;
            IndexBuffer& operator=(IndexBuffer&& rhs);

            void bind() const;
            void unbind() const;
            uint getCount() const;

        private:
            uint32_t m_id;
            uint m_count;
    };
};

#endif
