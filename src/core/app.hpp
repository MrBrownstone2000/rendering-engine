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
            void Init();
            void Run();

            void OnEvent(events::Event& e);

            void PushLayer(ILayer* layer);
            void PushOverlay(ILayer* overlay);

            inline static Application& Get() { return *ioc::Sing().Resolve<Application>(); }
            inline window::IWindow& GetWindow() { return *m_window; }

        private:
            bool OnWindowClose(events::WindowCloseEvent& e);
            bool OnKeyPressed(events::KeyPressedEvent& e);
            bool OnKeyReleased(events::KeyReleasedEvent& e);

        private:
            std::shared_ptr<window::IWindow> m_window;
            gui::ImGuiLayer* m_imGuiLayer;
            bool m_running = true;

            LayerStack m_layerStack;

            std::shared_ptr<renderer::Shader> shader;
            std::shared_ptr<renderer::VertexArray> vao;
    };
}

#endif
