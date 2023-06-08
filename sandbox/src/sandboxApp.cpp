#include <iostream>
#include <memory>
#include <vector>

#include "engine/engine.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"

namespace engine
{
    void UserBoot()
    {
        ioc::Get().Register<log::ISeverityLevelPolicy>([] {
                return std::make_shared<log::SeverityLevelPolicy>(log::Level::Debug);
                });
    }

    Application* GetApp()
    {
        return new engine::Application;
    }
}
