
#include "pch.hpp"
#include "app.hpp"
#include "boot.hpp"

using namespace engine;

int main()
{
    Boot();
    UserBoot();

    Application* app = GetApp();
    app->Run();
    delete app;

    return 0;
}
