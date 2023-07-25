#include "pch.hpp"
#include "app.hpp"
#include "events/eventDispatcher.hpp"
#include "ioc/singleton.hpp"
#include "layer.hpp"
#include "log/log.hpp"
#include "log/severityLevelPolicy.hpp"
#include "events/keyEvent.hpp"
#include "gfx/commands.hpp"
#include "renderer/renderer.hpp"

namespace engine
{
    Application::Application()
    {
        static bool isInit = false;
        if (isInit)
        {
            engineLog.fatal("There can only be one application !");
            exit(1);
        }
        isInit = true;

        m_window = ioc::Get().Resolve<window::IWindow>({.width = 800, .height = 600, .title = "Hi!"});
        m_window->setEventCallback(M_BIND_EVENT_FN(Application::onEvent));
    }

    void Application::init()
    {
        m_imGuiLayer = new gui::ImGuiLayer;
        pushOverlay(m_imGuiLayer);
        m_window->setImGuiCallback(m_imGuiLayer->GetEventCallback());
    }

    Application::~Application()
    {
    }

    void Application::onEvent(events::Event& e)
    {
        engineLog.verbose(e);

        events::EventDispatcher dispatcher(e);
        dispatcher.dispatch<events::WindowCloseEvent>(M_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.dispatch<events::KeyPressedEvent>(M_BIND_EVENT_FN(Application::onKeyPressed));

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            (*--it)->onEvent(e);
            if (e.isHandled())
                break;
        }
    }

    void Application::run()
    {
        while(m_running)
        {
            m_timer.tick();
            float dt = m_timer.dt();

            for (ILayer* layer : m_layerStack)
                layer->onUpdate(dt);

            m_imGuiLayer->beginFrame();
            for (ILayer* layer : m_layerStack)
                layer->onImGuiRender();
            m_imGuiLayer->endFrame();

            m_window->onUpdate();
            m_window->swapBuffers();
        }
    }

    void Application::pushLayer(ILayer* layer)
    {
        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(ILayer* overlay)
    {
        m_layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }


    bool Application::onWindowClose(events::WindowCloseEvent&)
    {
        m_running = false;
        return true;
    }

    bool Application::onKeyPressed(events::KeyPressedEvent& e)
    {
        if (e.getKeyCode() == input::KeyCode::Escape)
            m_running = false;
        return true;
    }

    bool Application::onKeyReleased(events::KeyReleasedEvent&)
    {
        return true;
    }
}
