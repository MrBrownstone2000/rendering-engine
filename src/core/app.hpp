#ifndef __APP_HPP__
#define __APP_HPP__

#include "../events/event.hpp"
#include "../events/windowEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../gui/imGuiManager.hpp"
#include "../gui/layerStack.hpp"
#include "../gui/imGuiViewport.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/vertexArray.hpp"
#include "../gfx/vertexBuffer.hpp"
#include "../gfx/indexBuffer.hpp"
#include "../window/window.hpp"
#include "../ioc/singleton.hpp"
#include "frameTimer.hpp"
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
            virtual void init();
            void run();
            void close();

            void pushLayer(ILayer* layer);
            void pushOverlay(ILayer* overlay);
            void addViewport(std::shared_ptr<ImGuiViewport> viewport);

            void onEvent(Event& e);
            void blockImGuiEvents(bool block) { return GetImGuiManager().blockEvents(block); }

            inline static Application& Get() { return *ioc::Sing().Resolve<Application>(); }
            inline Window& GetWindow() { return *m_window; }
            inline ImGuiManager& GetImGuiManager() { return m_imGuiManager; }

        private:
            bool onWindowClose(WindowCloseEvent& e);
            bool onKeyPressed(KeyPressedEvent& e);
            bool onKeyReleased(KeyReleasedEvent& e);

        private:
            std::shared_ptr<Window> m_window;
            ImGuiManager m_imGuiManager;
            bool m_running = true;

            std::vector<std::shared_ptr<ImGuiViewport>> m_viewports;
            LayerStack m_layerStack;
            FrameTimer m_timer;
    };
}

#endif
