#include "testCore/runner.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"

using namespace engine;

void Boot()
{
    log::Boot();

    // We can change the components used for logging before logging for the first time
    ioc::Get().Register<log::ISeverityLevelPolicy>([] {
        return std::make_shared<log::SeverityLevelPolicy>(log::Level::Debug);
    });
}

void f()
{
    engineLog.error("Error !");
}

int main()
{
    Boot();

    engineLog.fatal("Oh No!");
    engineLog.warn("warning");
    f();

    if (test::Run())
        return 0;
    return 1;
}
