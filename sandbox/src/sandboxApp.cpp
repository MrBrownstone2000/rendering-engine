#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"
#include "engine/gui/imguiLayer.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"

#include "engine/core/layer.hpp"

#include "engine/input/input.hpp"

namespace engine
{
    class ExampleLayer : public ILayer
    {
        public:
            void OnUpdate() override
            {
                if (input::Input::IsKeyPressed(input::KeyCode::Key_s))
                    engineLog.debug("Pressing key");
                if (input::Input::IsMouseButtonPressed(input::MouseButtonType::Left))
                    engineLog.debug("Pressing mouse");
                if (input::Input::IsKeyPressed(input::KeyCode::Space))
                    std::cout << input::Input::GetMouseX() << ", " << input::Input::GetMouseY() << std::endl;
            }

            void OnEvent(events::Event&) override
            {
            //    engineLog.debug(e);
            }
    };

    class Sandbox : public Application
    {
        public:
            Sandbox()
            {
                PushLayer(new ExampleLayer());
                PushLayer(new gui::ImGuiLayer());
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
    }

    Application* GetApp()
    {
        return new Sandbox;
    }
}
