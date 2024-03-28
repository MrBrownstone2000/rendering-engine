#include "pch.hpp"
#include "window/window.hpp"

#include "window/sdlWindow.hpp"
#include "ioc/container.hpp"


namespace engine
{
    namespace window
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

    void Window::setEventCallback(const EventCallback& cb)
    {
        m_eventCallback = cb;
    }

    void Window::setImGuiCallback(std::function<void(void*)> cb)
    { 
        m_imGuiEventCallback = cb;
    }
}
