#include "app.hpp"
#include "events/eventDispatcher.hpp"
#include "ioc/singleton.hpp"
#include "layer.hpp"
#include "log/log.hpp"
#include "log/severityLevelPolicy.hpp"
#include "events/keyEvent.hpp"

#include <GL/glew.h>

namespace engine
{
    Application* Application::s_instance = nullptr;

    Application::Application()
        : m_window(window::Create(800, 600, "Hi!"))
    {
        s_instance = this;

        m_imGuiLayer = new gui::ImGuiLayer;
        PushOverlay(m_imGuiLayer);

        m_window->SetEventCallback(M_BIND_EVENT_FN(Application::OnEvent));
        m_window->SetImGuiCallback(m_imGuiLayer->GetEventCallback());

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        float vertices[] = {
            -0.5, -0.5, 0,
            0.5, -0.5, 0,
            -0.5, 0.5, 0,
            0.5, 0.5, 0
        };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        uint indices[] = {
            0, 1, 2,
            2, 3, 1
        };

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        shader = renderer::Shader("../shaders/vertex_basic.glsl", "../shaders/frag_basic.glsl");
    }

    Application::~Application()
    {
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void Application::OnEvent(events::Event& e)
    {
        engineLog.verbose(e);

        events::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<events::WindowCloseEvent>(M_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<events::KeyPressedEvent>(M_BIND_EVENT_FN(Application::OnKeyPressed));

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.isHandled())
                break;
        }
    }

    void Application::Run()
    {
        while(m_running)
        {
            glClearColor(0, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(vao);
            shader.use();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            for (ILayer* layer : m_layerStack)
                layer->OnUpdate();

            m_imGuiLayer->Begin();
            for (ILayer* layer : m_layerStack)
                layer->OnImGuiRender();
            m_imGuiLayer->End();

            m_window->OnUpdate();
            m_window->SwapBuffers();
        }
    }

    void Application::PushLayer(ILayer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(ILayer* overlay)
    {
        m_layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }


    bool Application::OnWindowClose(events::WindowCloseEvent&)
    {
        m_running = false;
        return true;
    }

    bool Application::OnKeyPressed(events::KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == input::KeyCode::Escape)
            m_running = false;
        return true;
    }

    bool Application::OnKeyReleased(events::KeyReleasedEvent&)
    {
        return true;
    }
}
