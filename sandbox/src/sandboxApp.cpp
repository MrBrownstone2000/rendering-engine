#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"
#include "engine/gui/imguiLayer.hpp"

#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"
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
                if (input::IsKeyPressed(input::KeyCode::Key_s))
                    engineLog.debug("Pressing key");
                if (input::IsMouseButtonPressed(input::MouseButtonType::Left))
                    engineLog.debug("Pressing mouse");
                if (input::IsKeyPressed(input::KeyCode::Space))
                    std::cout << input::GetMouseX() << ", " << input::GetMouseY() << std::endl;
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
