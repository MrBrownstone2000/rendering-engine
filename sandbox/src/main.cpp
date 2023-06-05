#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"
#include "engine/util/assert.hpp"

#include "engine/window/window.hpp"
#include "engine/events/mouseEvent.hpp"

#include <GL/glew.h>
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

    events::MouseButtonPressedEvent e(666);
    engineLog.info(e);

    std::unique_ptr<window::IWindow> w = window::Create(800, 600, "HI");
    while(w->OnUpdate())
    {
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        w->SwapBuffers();
    }

    return 0;
}
