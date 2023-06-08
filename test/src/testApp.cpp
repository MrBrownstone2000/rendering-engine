#include "engine/engine.hpp"

// These funcitons need a definition, but the main function
// in the engine is not called (It seems like it is overloaded by the one
// in the test suite.
namespace engine
{
    void UserBoot() { }

    Application* GetApp() { return nullptr; }
}
