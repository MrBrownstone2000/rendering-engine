#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"

#include "engine/core/layer.hpp"


namespace engine
{
    class ExampleLayer : public ILayer
    {
        public:
            void OnUpdate() override
            {
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
    }

    Application* GetApp()
    {
        return new Sandbox;
    }
}
