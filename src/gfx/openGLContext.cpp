#include "pch.hpp"
#include "gfx/openGLContext.hpp"
#include "GL/glew.h"

namespace engine
{
    OpenGLContext::OpenGLContext(SDL_Window* window)
        : m_window(window)
    {
        m_context = SDL_GL_CreateContext(m_window);
        Check(m_context).msg("Error: [GL] failed to get GL context from window");
        std::stringstream ss;
        ss << "OpenGL Context:" << std::endl;
        ss << "    Vendor: " << glGetString(GL_VENDOR) << std::endl;
        ss << "    Renderer: " << glGetString(GL_RENDERER) << std::endl;
        ss << "    Version: " << glGetString(GL_VERSION) << std::endl;
        engineLog.info(ss.str());

        SDL_GL_MakeCurrent(m_window, m_context);
    }

    OpenGLContext::~OpenGLContext()
    {
        SDL_GL_DeleteContext(m_context);
    }

    void OpenGLContext::swapBuffers()
    {
        SDL_GL_SwapWindow(m_window);
    }

    void* OpenGLContext::getNativeContext()
    {
        return &m_context;
    }
}
