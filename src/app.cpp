#include "app.hpp"
#include "events/eventDispatcher.hpp"
#include "ioc/container.hpp"
#include "log/log.hpp"
#include "log/severityLevelPolicy.hpp"

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
        engineLog.info(e); 

        events::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<events::WindowCloseEvent>(M_BIND_EVENT_CB(OnWindowClose));
    }

    void Application::Run()
    {
        while(m_running)
        {
            m_window->OnUpdate();
            glClearColor(0, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->SwapBuffers();
        }
    }

    bool Application::OnWindowClose(events::WindowCloseEvent&)
    {
        m_running = false;
        return true;
    }
#undef M_BIND_EVENT_CB
}
