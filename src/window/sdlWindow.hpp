#ifndef __SDLWINDOW_HPP__
#define __SDLWINDOW_HPP__

#include "window.hpp"
#include <memory>

namespace engine::window
{
    class WindowImpl;
    class SDLWindow : public Window
    {
        public:
            SDLWindow(uint width, uint height);
            ~SDLWindow();

            bool OnUpdate();
            void SwapBuffers();

        private:
            std::unique_ptr<WindowImpl> m_pImpl;
    };
}

#endif
