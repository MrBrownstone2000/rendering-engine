#include "app.hpp"
#include "events/eventDispatcher.hpp"
#include "ioc/container.hpp"
#include "layer.hpp"
#include "log/log.hpp"
#include "log/severityLevelPolicy.hpp"
#include "events/keyEvent.hpp"

#include <GL/glew.h>

namespace engine
{
#define M_BIND_EVENT_CB(fun) std::bind(&Application::fun, this, std::placeholders::_1)
    Application::Application()
        : m_window(window::Create(800, 600, "Hi!"))
    {
        m_window->SetEventCallback(M_BIND_EVENT_CB(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(events::Event& e)
    {
        engineLog.verbose(e);

        events::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<events::WindowCloseEvent>(M_BIND_EVENT_CB(OnWindowClose));
        dispatcher.Dispatch<events::KeyPressedEvent>(M_BIND_EVENT_CB(OnKeyPressed));

        for (auto it = m_layerStack.end(); it != m_layerStack.begin(); --it)
        {
            (*it)->OnEvent(e);
            if (e)
                break;
        }
    }

    void Application::Run()
    {
        while(m_running)
        {
            glClearColor(0, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (ILayer* layer : m_layerStack)
                layer->OnUpdate();

            m_window->OnUpdate();
            m_window->SwapBuffers();
        }
    }

    void Application::PushLayer(ILayer* layer)
    {
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(ILayer* overlay)
    {
        m_layerStack.PushOverlay(overlay);
    }


    bool Application::OnWindowClose(events::WindowCloseEvent&)
    {
        m_running = false;
        return true;
    }

    bool Application::OnKeyPressed(events::KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == events::KeyCode::Escape)
            m_running = false;
        return true;
    }

    bool Application::OnKeyReleased(events::KeyReleasedEvent&)
    {
        return true;
    }
#undef M_BIND_EVENT_CB
}
