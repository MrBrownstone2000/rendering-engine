
#include "pch.hpp"
#include "app.hpp"
#include "boot.hpp"

using namespace engine;

int main()
{
    Boot();
    UserBoot();
    engineLog.info("Engine has Booted");

    Application* app = GetApp();
    app->Run();
    delete app;

    return 0;
}
