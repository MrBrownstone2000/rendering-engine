#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"

#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"
#include "engine/log/severityLevelPolicy.hpp"


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

                vao = std::make_shared<renderer::VertexArray>();
                vao->attachVertexBuffer(vbo);
                vao->attachIndexBuffer(renderer::IndexBuffer(indices, 6));

                renderer::Shader::setIncludeDirs({ "../shaders" });
                shader = std::make_shared<renderer::Shader>("vertex_basic.glsl", "frag_basic.glsl");

                renderer::setClearColor(0, 0, 1);
            }

            void onUpdate() override
            {
                renderer::Renderer::beginFrame();
                renderer::Renderer::submit(shader, vao);
                renderer::Renderer::endFrame();

                // if (input::IsKeyPressed(input::KeyCode::Key_s))
                //     engineLog.debug("Pressing key");
                // if (input::IsMouseButtonPressed(input::MouseButtonType::Left))
                //     engineLog.debug("Pressing mouse");
                // if (input::IsKeyPressed(input::KeyCode::Space))
                //     std::cout << input::GetMouseX() << ", " << input::GetMouseY() << std::endl;
            }

            void onEvent(events::Event&) override
            {
            }

        private:
            std::shared_ptr<renderer::Shader> shader;
            std::shared_ptr<renderer::VertexArray> vao;
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
