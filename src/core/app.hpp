#ifndef __APP_HPP__
#define __APP_HPP__

#include "../events/event.hpp"
#include "../events/windowEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../window/window.hpp"
#include <memory>

namespace engine
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(events::Event& e);

        private:
            bool OnWindowClose(events::WindowCloseEvent& e);
            bool OnKeyPressed(events::KeyPressedEvent& e);
            bool OnKeyReleased(events::KeyReleasedEvent& e);

        private:
            std::unique_ptr<window::IWindow> m_window;
            bool m_running = true;
    };
    Application* GetApp();
    void UserBoot();
}

#endif
