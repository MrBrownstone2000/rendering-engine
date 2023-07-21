#include "pch.hpp"
#include "app.hpp"
#include "events/eventDispatcher.hpp"
#include "ioc/singleton.hpp"
#include "layer.hpp"
#include "log/log.hpp"
#include "log/severityLevelPolicy.hpp"
#include "events/keyEvent.hpp"
#include "renderer/commands.hpp"
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

        float vertices[] = {
            -0.5, -0.5, 0, 1, 0, 0, 1,
            0.5, -0.5, 0, 0, 1, 0, 1,
            -0.5, 0.5, 0, 0, 0, 1, 1,
            0.5, 0.5, 0, 1, 0, 1, 1,
        };

        std::shared_ptr<renderer::VertexBuffer> vbo = std::make_shared<renderer::VertexBuffer>(vertices, sizeof(vertices));

        vbo->setLayout({
            { renderer::ShaderDataType::float3, "pos" },
            { renderer::ShaderDataType::float4, "col" },
        });

        uint indices[] = {
            0, 1, 2,
            2, 3, 1
        };

        vao = std::make_shared<renderer::VertexArray>();
        vao->attachVertexBuffer(vbo);
        vao->attachIndexBuffer(renderer::IndexBuffer(indices, 6));

        renderer::Shader::setIncludeDirs({ "../shaders" });
        shader = std::make_shared<renderer::Shader>("vertex_basic.glsl", "frag_basic.glsl");

        renderer::setClearColor(0, 0, 1);
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
        dispatcher.Dispatch<events::WindowCloseEvent>(M_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.Dispatch<events::KeyPressedEvent>(M_BIND_EVENT_FN(Application::onKeyPressed));

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
            renderer::Renderer::beginFrame();
            renderer::Renderer::submit(shader, vao);
            renderer::Renderer::endFrame();

            for (ILayer* layer : m_layerStack)
                layer->onUpdate();

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
