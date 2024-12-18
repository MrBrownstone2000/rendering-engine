#ifndef __OPENGLCONTEXT_HPP__
#define __OPENGLCONTEXT_HPP__

#include "SDL_video.h"
#include "context.hpp"

namespace engine
{
    class OpenGLContext : public IRenderingContext
    {
        public:
            OpenGLContext(SDL_Window* window);
            ~OpenGLContext();

            void swapBuffers() override;
            void* getNativeContext() override;

        private:
            SDL_Window* m_window;
            SDL_GLContext m_context;
    };
}

#endif
