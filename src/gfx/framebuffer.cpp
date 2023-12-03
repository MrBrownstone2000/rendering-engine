#include "pch.hpp"
#include "framebuffer.hpp"

#include <GL/glew.h>

namespace engine
{
    Framebuffer::Framebuffer()
        : m_id(0), m_colorAttachment(0)
    {
    }

    Framebuffer::Framebuffer(const FrameBufferParams& specs)
        : m_params(specs)
    {
        resize();
    }

    void Framebuffer::resize()
    {
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteRenderbuffers(1, &m_depthAttachment);
        glDeleteFramebuffers(1, &m_id);
        
        glCreateFramebuffers(1, &m_id);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
        glTextureParameteri(m_colorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_colorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureStorage2D(m_colorAttachment, 1, GL_RGB8, m_params.width, m_params.height);
        glNamedFramebufferTexture(m_id, GL_COLOR_ATTACHMENT0, m_colorAttachment, 0);

        glCreateRenderbuffers(1, &m_depthAttachment);
        glNamedRenderbufferStorage(m_depthAttachment, GL_DEPTH24_STENCIL8, m_params.width, m_params.height);
        glNamedFramebufferRenderbuffer(m_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);

        if (glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            engineLog.error("Couldn't create framebuffer...");
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteRenderbuffers(1, &m_depthAttachment);
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteFramebuffers(1, &m_id);
    }

    Framebuffer::Framebuffer(Framebuffer&& rhs)
    {
        m_id = rhs.m_id;
        m_colorAttachment = rhs.m_colorAttachment;
        m_depthAttachment = rhs.m_depthAttachment;
        rhs.m_id = 0;
        rhs.m_colorAttachment = 0;
        rhs.m_depthAttachment = 0;
        m_params = std::move(rhs.m_params);
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& rhs)
    {
        m_id = rhs.m_id;
        m_colorAttachment = rhs.m_colorAttachment;
        m_depthAttachment = rhs.m_depthAttachment;
        rhs.m_id = 0;
        rhs.m_colorAttachment = 0;
        rhs.m_depthAttachment = 0;
        m_params = std::move(rhs.m_params);
        return *this;
    }

    void Framebuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }

    void Framebuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::resize(uint32_t width, uint32_t height)
    {
        m_params.width = width;
        m_params.height = height;
        resize();
    }

    uint32_t Framebuffer::getTextureId() const
    {
        return m_colorAttachment;
    }
}
