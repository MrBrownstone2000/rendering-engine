#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"

#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"
#include "engine/log/severityLevelPolicy.hpp"

#include "engine/renderer/camera.hpp"
#include "engine/events/eventDispatcher.hpp"
#include "engine/events/viewportEvent.hpp"
#include "engine/renderer/mesh.hpp"
#include "engine/gfx/texture.hpp"
#include "engine/util/observer.hpp"
#include "engine/gui/imGuiViewport.hpp"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace engine
{
    class ExampleLayer : public ILayer, public util::IObserver
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
                m_fb = std::make_shared<Framebuffer>(params);

                m_viewport = std::make_shared<ImGuiViewport>(m_fb);
                m_viewport->subscribe(this);
                Application::Get().addViewport(m_viewport);
            }

            void onUpdate(float dt) override
            {
                if (m_viewport->isFocused())
                    m_camera.update(dt);
            }

            void onNotify() override
            {
                render();
            }

            void render()
            {
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

            bool onViewportResize(const ViewportResizeEvent& event)
            {
                if (event.getViewport() == m_viewport.get())
                    m_camera.setWindowSize(event.getWidth(), event.getHeight());
                return false;
            }

            void onEvent(Event& event) override
            {
                EventDispatcher d(event);
                d.dispatch<WindowResizeEvent>(M_BIND_EVENT_FN(ExampleLayer::onWindowResize));
                d.dispatch<MouseScrolledEvent>(M_BIND_EVENT_FN(ExampleLayer::onMouseScroll));
                d.dispatch<ViewportResizeEvent>(M_BIND_EVENT_FN(ExampleLayer::onViewportResize));
            }

            void onImGuiRender() override
            {
            }

        private:
            std::shared_ptr<Shader> m_shader;
            std::shared_ptr<Texture> m_texture_smiley;
            std::shared_ptr<Texture> m_texture_window;
            std::shared_ptr<Framebuffer> m_fb;
            Mesh m_mesh;
            glm::mat4 m_model1, m_model2;
            Camera m_camera;

            std::shared_ptr<ImGuiViewport> m_viewport;
    };

    class Sandbox : public Application
    {
        public:
            Sandbox()
            {
            }

            void init() override
            {
                Application::init();
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
