#ifndef __APP_HPP__
#define __APP_HPP__

#include "layerStack.hpp"
#include "../events/event.hpp"
#include "../events/windowEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../gui/imguiLayer.hpp"
#include "../renderer/shader.hpp"
#include "../window/window.hpp"
#include <memory>
#include <GL/glew.h>

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

            static Application& Get() { return *s_instance; }
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

            static Application* s_instance;

            renderer::Shader shader;
            GLuint vao, vbo, ebo;
    };
    void UserBoot();
    Application* CreateApplication();
}

#endif
