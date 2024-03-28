#ifndef __FRAMEBUFFER_HPP__
#define __FRAMEBUFFER_HPP__

#include "../util/types.hpp"

namespace engine
{
    struct FrameBufferParams
    {
        uint32_t width = 1; 
        uint32_t height = 1;
        uint32_t samples = 1;
    };
    class Framebuffer
    {
        public:

            Framebuffer();
            Framebuffer(const FrameBufferParams& specs);
            ~Framebuffer();

            Framebuffer(const Framebuffer& rhs) = delete;
            Framebuffer(Framebuffer&& rhs);
            Framebuffer& operator=(const Framebuffer& rhs) = delete;
            Framebuffer& operator=(Framebuffer&& rhs);

            void bind() const;
            void unbind() const;

            void resize(uint32_t width, uint32_t height);

            uint32_t getTextureId() const;
            uint32_t getWidth() const;
            uint32_t getHeight() const;

        private:
            void resize();

        private:
            uint32_t m_id;
            uint32_t m_colorAttachment;
            uint32_t m_depthAttachment;
            FrameBufferParams m_params;
    };
}

#endif
