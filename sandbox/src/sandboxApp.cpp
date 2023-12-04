#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"

#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"
#include "engine/log/severityLevelPolicy.hpp"

#include "engine/renderer/camera.hpp"
#include "engine/events/eventDispatcher.hpp"
#include "engine/renderer/mesh.hpp"
#include "engine/gfx/texture.hpp"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace engine
{
    class ExampleLayer : public ILayer
    {
        public:
            ExampleLayer()
            {
                std::vector<Vertex> vertices = {
                    {{ -0.5, -0.5, 0 }, {1, 0, 1}, {0, 0}},
                    {{ 0.5, -0.5, 0 }, {1, 0, 1}, {1, 0}},
                    {{ -0.5, 0.5, 0 }, {1, 0, 1}, {0, 1}},
                    {{ 0.5, 0.5, 0 }, {1, 0, 1}, {1, 1}}
                };

                std::vector<uint32_t> indices = {
                    0, 1, 2,
                    2, 3, 1
                };

                m_mesh = Mesh(std::move(vertices), std::move(indices));

                Shader::setIncludeDirs({ "../shaders" });
                m_shader = std::make_shared<Shader>("vertex_basic.glsl", "frag_basic.glsl");

                renderer::setClearColor(0.2, 0.2, 0.2);

                m_camera.setPosition({0, 0, -1});
                m_camera.setYaw(90);
                m_texture_smiley = std::make_shared<Texture>("../data/smiley.png");
                m_texture_window = std::make_shared<Texture>("../data/window.png");

                m_model1 = glm::mat4(1);
                m_model2 = glm::translate(glm::mat4(1), glm::vec3(1, 0, 1));

                FrameBufferParams params;
                params.width = 1280;
                params.height = 720;
                m_size = ImVec2(1280, 720);
                m_fb = std::make_shared<Framebuffer>(params);
            }

            void onUpdate(float dt) override
            {
                if (m_isViewportFocused)
                    m_camera.update(dt);

                m_shader->bind();
                renderer::beginFrame(m_fb, m_camera);

                renderer::submit(m_shader, m_texture_smiley, m_model2, m_mesh);

                renderer::submit(m_shader, m_texture_window, m_model1, m_mesh);

                renderer::endFrame();
            }

            bool onWindowResize(const WindowResizeEvent& event)
            {
                m_camera.setWindowSize(event.getWidth(), event.getHeight());
                return false;
            }

            bool onMouseScroll(const MouseScrolledEvent& event)
            {
                m_camera.changeFOV(event.getY());
                return false;
            }

            void onEvent(Event& event) override
            {
                EventDispatcher d(event);
                d.dispatch<WindowResizeEvent>(M_BIND_EVENT_FN(ExampleLayer::onWindowResize));
                d.dispatch<MouseScrolledEvent>(M_BIND_EVENT_FN(ExampleLayer::onMouseScroll));
            }

            void onImGuiRender() override
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                ImGui::Begin("Scene");
                
                m_isViewportFocused = ImGui::IsWindowFocused();
                m_isViewportHovered = ImGui::IsWindowHovered();
                Application::Get().blockImGuiEvents(!m_isViewportFocused || !m_isViewportHovered);

                ImVec2 size  = ImGui::GetContentRegionAvail();
                if (size.x != m_size.x || size.y != m_size.y)
                {
                    m_size = size;
                    m_fb->resize(size.x, size.y);
                    glViewport(0, 0, size.x, size.y);
                    m_camera.setWindowSize(size.x, size.y);
                }

                ImGui::Image((void*) m_fb->getTextureId(), size);

                ImGui::End();
                ImGui::PopStyleVar();

            }

        private:
            std::shared_ptr<Shader> m_shader;
            std::shared_ptr<Texture> m_texture_smiley;
            std::shared_ptr<Texture> m_texture_window;
            std::shared_ptr<Framebuffer> m_fb;
            bool m_isViewportFocused = false;
            bool m_isViewportHovered = false;
            Mesh m_mesh;
            glm::mat4 m_model1, m_model2;

            Camera m_camera;
            ImVec2 m_size;
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
