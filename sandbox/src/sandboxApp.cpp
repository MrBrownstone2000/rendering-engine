#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"
#include "engine/util/assert.hpp"

#include "engine/window/window.hpp"
#include "engine/events/mouseEvent.hpp"

#include "engine/app.hpp"
#include "engine/boot.hpp"

#include <GL/glew.h>

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
