#ifndef __APP_HPP__
#define __APP_HPP__

#include "layerStack.hpp"
#include "../events/event.hpp"
#include "../events/windowEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../gui/imguiLayer.hpp"
#include "../renderer/shader.hpp"
#include "../renderer/vertexArray.hpp"
#include "../renderer/vertexBuffer.hpp"
#include "../renderer/indexBuffer.hpp"
#include "../window/window.hpp"
#include "../ioc/singleton.hpp"
#include <memory>

namespace engine
{
    class ILayer;

    class Application
    {
        public:
            Application();
            virtual ~Application();

            // For initializations that need Application::Get()
            void init();
            void run();

            void onEvent(events::Event& e);

            void pushLayer(ILayer* layer);
            void pushOverlay(ILayer* overlay);

            inline static Application& Get() { return *ioc::Sing().Resolve<Application>(); }
            inline window::IWindow& GetWindow() { return *m_window; }

        private:
            bool onWindowClose(events::WindowCloseEvent& e);
            bool onKeyPressed(events::KeyPressedEvent& e);
            bool onKeyReleased(events::KeyReleasedEvent& e);

        private:
            std::shared_ptr<window::IWindow> m_window;
            gui::ImGuiLayer* m_imGuiLayer;
            bool m_running = true;

            LayerStack m_layerStack;
    };
}

#endif
