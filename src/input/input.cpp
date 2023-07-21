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
        return ioc::Sing().Resolve<IInput>()->isKeyPressed(key);
    }

    bool IsMouseButtonPressed(MouseButtonType button)
    {
        return ioc::Sing().Resolve<IInput>()->isMouseButtonPressed(button);
    }

    float GetMouseX()
    {
        return ioc::Sing().Resolve<IInput>()->getMouseX();
    }

    float GetMouseY() 
    { 
        return ioc::Sing().Resolve<IInput>()->getMouseY(); 
    }
}
