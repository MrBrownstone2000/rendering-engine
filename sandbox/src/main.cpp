#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"
#include "engine/util/assert.hpp"

#include "engine/window/window.hpp"

using namespace engine;

void Boot()
{

    log::Boot();
    window::Boot();

    // We can change the components used for logging before logging for the first time
    ioc::Get().Register<log::ISeverityLevelPolicy>([] {
        return std::make_shared<log::SeverityLevelPolicy>(log::Level::Debug);
    });

    engineLog.info("Engine has Booted");
}

int main()
{
    Boot();

    std::unique_ptr<window::Window> w = window::Create(800, 600);
    while(w->OnUpdate())
    {
        w->SwapBuffers();
    }

    return 0;
}
