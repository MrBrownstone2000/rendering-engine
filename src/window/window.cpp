#include "pch.hpp"
#include "window.hpp"
#include "sdlWindow.hpp"
#include "ioc/container.hpp"


namespace engine::window
{
    void Boot()
    {
        SDLWindow::Boot();
    }

    std::shared_ptr<Window> Create(const WindowParams& params)
    {
        return std::make_shared<SDLWindow>(params);
    }
}
