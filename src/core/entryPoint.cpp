
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

    Application* app = CreateApplication();
    app->Run();
    delete app;

    return 0;
}
