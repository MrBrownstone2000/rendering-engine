#include "pch.hpp"
#include "app.hpp"
#include "events/eventDispatcher.hpp"
#include "ioc/singleton.hpp"
#include "gui/layer.hpp"
#include "log/log.hpp"
#include "log/severityLevelPolicy.hpp"
#include "events/keyEvent.hpp"
#include "gfx/commands.hpp"
#include "renderer/renderer.hpp"

#include "imgui/imgui.h"

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

        m_window = window::Create({.width = 800, .height = 600, .title = "Hi!"});
        m_window->setEventCallback(M_BIND_EVENT_FN(Application::onEvent));
    }

    void Application::init()
    {
        m_imGuiManager.init();
        m_window->setImGuiCallback(m_imGuiManager.GetEventCallback());
    }

    void Application::close()
    {
        m_running = false;
    }

    Application::~Application()
    {
    }

    void Application::onEvent(Event& e)
    {
        engineLog.verbose(e);

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(M_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.dispatch<KeyPressedEvent>(M_BIND_EVENT_FN(Application::onKeyPressed));

        m_imGuiManager.onEvent(e);
        if (e.isHandled())
            return;

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

            m_imGuiManager.beginFrame();

            for (auto v : m_viewports)
                v->onImGuiRender();

            for (ILayer* layer : m_layerStack)
                layer->onImGuiRender();

            static bool show = true;
            ImGui::ShowDemoWindow(&show);

            m_imGuiManager.endFrame();

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

    void Application::addViewport(std::shared_ptr<ImGuiViewport> viewport)
    {
        viewport->setEventCallback(M_BIND_EVENT_FN(Application::onEvent));
        m_viewports.push_back(viewport);
    }

    bool Application::onWindowClose(WindowCloseEvent&)
    {
        m_running = false;
        return false;
    }

    bool Application::onKeyPressed(KeyPressedEvent& e)
    {
        if (e.getKeyCode() == KeyCode::Escape)
            m_running = false;
        return false;
    }

    bool Application::onKeyReleased(KeyReleasedEvent&)
    {
        return false;
    }
}
