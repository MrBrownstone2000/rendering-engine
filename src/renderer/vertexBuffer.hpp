#ifndef __VERTEXBUFFER_HPP__
#define __VERTEXBUFFER_HPP__

#include "../util/types.hpp"
#include <GL/glew.h>

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

            void bind() const;
            void unbind() const;

        private:
            GLuint m_id;
    };
};

#endif
