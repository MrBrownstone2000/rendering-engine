#ifndef __OPENGLCONTEXT_HPP__
#define __OPENGLCONTEXT_HPP__

#include "SDL_video.h"
#include "renderer/context.hpp"

namespace engine::renderer
{
    class OpenGLContext : public IContext
    {
        public:
            OpenGLContext(SDL_Window* window);
            void SwapBuffers() override;

        private:
            SDL_Window* m_window;
            SDL_GLContext m_context;
    };
}

#endif
