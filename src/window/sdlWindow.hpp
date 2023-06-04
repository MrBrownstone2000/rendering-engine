#ifndef __SDLWINDOW_HPP__
#define __SDLWINDOW_HPP__

#include "window.hpp"
#include "../renderer/context.hpp"
#include <SDL.h>
#include <memory>

namespace engine::window
{
    class WindowImpl;
    class SDLWindow : public IWindow
    {
        public:
            SDLWindow(uint width, uint height);
            ~SDLWindow();

            bool OnUpdate();
            void SwapBuffers();

        private:
            SDL_Window* m_window;
            std::unique_ptr<renderer::IContext> m_context;

            static inline bool m_isGlewInit = false;
    };
}

#endif
