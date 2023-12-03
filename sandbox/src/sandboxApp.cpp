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
                // m_camera.update(dt);

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

            void onEvent(Event& event) override
            {
                EventDispatcher d(event);
                d.dispatch<WindowResizeEvent>(M_BIND_EVENT_FN(ExampleLayer::onWindowResize));
            }

            void onImGuiRender() override
            {
                testDockspace();

                
                ImGuiWindowFlags window_flags = 0; // ImGuiWindowFlags_NoCollapse;

                ImGui::Begin("Scene", nullptr, window_flags);

                ImVec2 size  = ImGui::GetContentRegionAvail();
                if (size.x != m_size.x || size.y != m_size.y)
                {
                    m_size = size;
                    m_fb->resize(size.x, size.y);
                    glViewport(0, 0, size.x, size.y);
                }
                //     recreate Framebuffer
                //     glViewport
                //     recompute projection matrix ?
                // https://www.youtube.com/watch?v=ETIhjdVBH-8&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=74

                ImGui::Image((void*) m_fb->getTextureId(), size);

                ImGui::End();

            }

            void testDockspace()
            {
                static bool dockspaceEnabled = true;
                static bool opt_fullscreen = true;
                static bool opt_padding = false;
                static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

                // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
                // because it would be confusing to have two docking targets within each others.
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
                if (opt_fullscreen)
                {
                    const ImGuiViewport* viewport = ImGui::GetMainViewport();
                    ImGui::SetNextWindowPos(viewport->WorkPos);
                    ImGui::SetNextWindowSize(viewport->WorkSize);
                    ImGui::SetNextWindowViewport(viewport->ID);
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
                }
                else
                {
                    dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
                }

                // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
                // and handle the pass-thru hole, so we ask Begin() to not render a background.
                if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                    window_flags |= ImGuiWindowFlags_NoBackground;

                // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
                // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
                // all active windows docked into it will lose their parent and become undocked.
                // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
                // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
                if (!opt_padding)
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
                ImGui::Begin("DockSpace Demo", &dockspaceEnabled, window_flags);
                if (!opt_padding)
                    ImGui::PopStyleVar();

                if (opt_fullscreen)
                    ImGui::PopStyleVar(2);

                // Submit the DockSpace
                ImGuiIO& io = ImGui::GetIO();
                if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
                {
                    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
                }
                else
                {
                    // ShowDockingDisabledMessage();
                    engineLog.error("Docking disabled");
                }

                if (ImGui::BeginMenuBar())
                {
                    if (ImGui::BeginMenu("Options"))
                    {
                        // Disabling fullscreen would allow the window to be moved to the front of other windows,
                        // which we can't undo at the moment without finer window depth/z control.

                        if (ImGui::MenuItem("Close"))
                            Application::Get().close();
                        ImGui::EndMenu();
                    }

                    ImGui::EndMenuBar();
                }

                ImGui::End();
            }

        private:
            std::shared_ptr<Shader> m_shader;
            std::shared_ptr<Texture> m_texture_smiley;
            std::shared_ptr<Texture> m_texture_window;
            std::shared_ptr<Framebuffer> m_fb;
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
