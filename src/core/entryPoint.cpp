
#include "pch.hpp"
#include "app.hpp"
#include "boot.hpp"
#include "ioc/singleton.hpp"

using namespace engine;

int main()
{
    Boot();
    UserBoot();
    engineLog.info("Engine has Booted");

    std::shared_ptr<Application> app = ioc::Sing().Resolve<Application>();
    app->Init();
    app->Run();

    return 0;
}
