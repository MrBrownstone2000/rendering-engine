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

using namespace engine;

int main()
{
    engine::Boot();

    // We can change the components used for logging before logging for the first time
    ioc::Get().Register<log::ISeverityLevelPolicy>([] {
        return std::make_shared<log::SeverityLevelPolicy>(log::Level::Debug);
    });

    engine::Application app;
    app.Run();

    return 0;
}
