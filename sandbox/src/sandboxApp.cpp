#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"

#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"
#include "engine/log/severityLevelPolicy.hpp"

#include "engine/renderer/camera.hpp"
#include "engine/events/eventDispatcher.hpp"


namespace engine
{
    class ExampleLayer : public ILayer
    {
        public:
            ExampleLayer()
            {
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

                m_vao = std::make_shared<renderer::VertexArray>();
                m_vao->attachVertexBuffer(vbo);
                m_vao->attachIndexBuffer(renderer::IndexBuffer(indices, 6));

                renderer::Shader::setIncludeDirs({ "../shaders" });
                m_shader = std::make_shared<renderer::Shader>("vertex_basic.glsl", "frag_basic.glsl");

                renderer::setClearColor(0, 0, 1);

                m_camera.setPosition({1, 1, 1});
            }

            void onUpdate() override
            {
                m_camera.update(1.);

                renderer::beginFrame(m_camera);
                renderer::submit(m_shader, m_vao);
                renderer::endFrame();
            }

            bool onWindowResize(const events::WindowResizeEvent& event)
            {
                m_camera.setWindowSize(event.getWidth(), event.getHeight());
                return false;
            }

            void onEvent(events::Event& event) override
            {
                events::EventDispatcher d(event);
                d.dispatch<events::WindowResizeEvent>(M_BIND_EVENT_FN(ExampleLayer::onWindowResize));
            }

        private:
            std::shared_ptr<renderer::Shader> m_shader;
            std::shared_ptr<renderer::VertexArray> m_vao;

            renderer::Camera m_camera;
    };

    class Sandbox : public Application
    {
        public:
            Sandbox()
            {
                pushLayer(new ExampleLayer());

            }

            ~Sandbox()
            {
            }
    };

    void UserBoot()
    {
        ioc::Get().Register<log::ISeverityLevelPolicy>([] {
            return std::make_shared<log::SeverityLevelPolicy>(log::Level::Debug);
        });

        ioc::Sing().Register<Application>([] {
            return std::make_shared<Sandbox>();
        });
    }
}
