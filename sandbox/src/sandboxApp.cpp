#include <iostream>
#include <memory>
#include <vector>

#include "Engine/engine.hpp"

#include "Engine/ioc/container.hpp"
#include "Engine/ioc/singleton.hpp"
#include "Engine/log/severityLevelPolicy.hpp"

#include "Engine/renderer/camera.hpp"
#include "Engine/events/eventDispatcher.hpp"
#include "Engine/events/viewportEvent.hpp"
#include "Engine/renderer/mesh.hpp"
#include "Engine/renderer/cameraController.hpp"
#include "Engine/gfx/texture.hpp"
#include "Engine/util/observer.hpp"
#include "Engine/gui/imGuiViewport.hpp"

#include "Engine/assets/importer.hpp"

#include "imgui.h"

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

                Shader::setIncludeDirs({ "shaders" });
                // m_shader = std::make_shared<Shader>("vertex_basic.glsl", "frag_basic.glsl");
                m_shader = std::make_shared<Shader>("vertex_basic.glsl", "frag_debug.glsl");

                renderer::setClearColor(0.2, 0.2, 0.2);

                auto cameraModel = std::make_shared<PerspectiveCamera>();
                cameraModel->setPosition({0, 0, -1});
                m_camera = PerspectiveCameraController(cameraModel);
                m_camera.setYaw(90);
                m_camera.setSpeed(1);

                m_texture_smiley = std::make_shared<Texture>("data/smiley.png");
                m_texture_window = std::make_shared<Texture>("data/window.png");
                m_model = AssetImporter::Import("data/robot.gltf");
                // m_model = AssetImporter::Import("data/cube.gltf");

                m_model1 = glm::mat4(1);
                m_model2 = glm::translate(glm::mat4(1), glm::vec3(1, 0, 1));

                FrameBufferParams params;
                m_fb = std::make_shared<Framebuffer>(params);

                m_viewport = std::make_shared<ImGuiViewport>(m_fb);
                m_viewport->subscribe(this);
                Application::Get().addViewport(m_viewport);
                m_camera.setViewport(m_viewport);
            }

            void onUpdate(float dt) override
            {
                if (m_viewport->isFocused())
                    m_camera.update(dt);
                m_model1 = glm::rotate(m_model1, dt, glm::vec3(0, 1, 0));
            }

            void onNotify() override
            {
                render();
            }

            void render()
            {
                m_shader->bind();
                renderer::beginFrame(m_fb, m_camera.getCamera());

                // renderer::submit(m_shader, m_texture_smiley, m_model2, m_mesh);
                // renderer::submit(m_shader, m_texture_window, m_model1, m_mesh);
                renderer::submit(m_shader, m_texture_window, m_model1, m_model);

                renderer::endFrame();
            }

            void onEvent(Event& event) override
            {
                m_camera.onEvent(event);
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

            Model m_model;

            PerspectiveCameraController m_camera;

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
