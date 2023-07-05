#include "pch.hpp"
#include "window.hpp"
#include "sdlWindow.hpp"
#include "ioc/container.hpp"


namespace engine::window
{
    void Boot()
    {
        SDLWindow::Boot();
        ioc::Get().Register<IWindow>([] (const IWindow::IocParams& p) {
            return std::make_shared<SDLWindow>(std::move(p));
        });
    }
}
