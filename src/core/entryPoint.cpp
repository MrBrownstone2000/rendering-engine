#include "pch.hpp"
#include "core/app.hpp"
#include "core/boot.hpp"
#include "ioc/singleton.hpp"

using namespace engine;

int main()
{
    Boot();
    UserBoot();
    engineLog.info("Engine has Booted");

    std::shared_ptr<Application> app = ioc::Sing().Resolve<Application>();
    app->init();
    app->run();

    return 0;
}
