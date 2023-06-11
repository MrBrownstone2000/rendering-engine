#ifndef __APP_HPP__
#define __APP_HPP__

#include "layerStack.hpp"
#include "../events/event.hpp"
#include "../events/windowEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../window/window.hpp"
#include <memory>

namespace engine
{
    class ILayer;

    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(events::Event& e);

            void PushLayer(ILayer* layer);
            void PushOverlay(ILayer* overlay);

        private:
            bool OnWindowClose(events::WindowCloseEvent& e);
            bool OnKeyPressed(events::KeyPressedEvent& e);
            bool OnKeyReleased(events::KeyReleasedEvent& e);

        private:
            std::unique_ptr<window::IWindow> m_window;
            bool m_running = true;

            LayerStack m_layerStack;
    };
    Application* GetApp();
    void UserBoot();
}

#endif
