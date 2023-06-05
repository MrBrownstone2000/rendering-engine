#include "pch.hpp"
#include "openGLContext.hpp"

namespace engine::renderer
{
    OpenGLContext::OpenGLContext(SDL_Window* window)
        : m_window(window)
    {
        m_context = SDL_GL_CreateContext(m_window);
        Check(m_context).msg("Error: [GL] failed to get GL context from window");
    }

    OpenGLContext::~OpenGLContext()
    {
        SDL_GL_DeleteContext(m_context);
    }

    void OpenGLContext::SwapBuffers()
    {
        SDL_GL_SwapWindow(m_window);
    }
}
