#include <iostream>
#include <memory>
#include <vector>

#include "engine/log/log.hpp"

#include "engine/ioc/container.hpp"
#include "engine/log/severityLevelPolicy.hpp"
#include "engine/util/assert.hpp"

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

    try {
        int x = 0, y = 1;
        Check(x > y).msg("Ooop").watch(x).watch(y).ex();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    int i = 666;
    engineLog.msg("Hi !").watch(i).msg("Bye!!").level(log::Level::Info);

    return 0;
}
