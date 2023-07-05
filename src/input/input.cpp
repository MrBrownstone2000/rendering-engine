#include "pch.hpp"
#include "input.hpp"
#include "sdlInput.hpp"

#include "ioc/singleton.hpp"

namespace engine::input
{
    void Boot()
    {
        ioc::Sing().Register<IInput>([]{
            return std::make_shared<SDLInput>();
        });
    }

    bool IsKeyPressed(KeyCode key)
    { 
        return ioc::Sing().Resolve<IInput>()->IsKeyPressed(key);
    }

    bool IsMouseButtonPressed(MouseButtonType button)
    {
        return ioc::Sing().Resolve<IInput>()->IsMouseButtonPressed(button);
    }

    float GetMouseX()
    {
        return ioc::Sing().Resolve<IInput>()->GetMouseX();
    }

    float GetMouseY() 
    { 
        return ioc::Sing().Resolve<IInput>()->GetMouseY(); 
    }
}
