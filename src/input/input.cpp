#include "pch.hpp"
#include "input.hpp"
#include "sdlInput.hpp"

#include "ioc/singleton.hpp"

namespace engine::input
{
    void Boot()
    {
        ioc::Sing().Register<Input>([]{
            return std::make_shared<SDLInput>();
        });
    }

    Input* Input::GetDefault()
    {
        static std::shared_ptr<Input> input = ioc::Sing().Resolve<Input>();
        return input.get();
    }

    bool Input::IsKeyPressed(KeyCode key)
    { 
        return GetDefault()->IsKeyPressed_Impl(key);
    }

    bool Input::IsMouseButtonPressed(MouseButtonType button)
    {
        return GetDefault()->IsMouseButtonPressed_Impl(button);
    }

    float Input::GetMouseX()
    {
        return GetDefault()->GetMouseX_Impl();
    }

    float Input::GetMouseY() 
    { 
        return GetDefault()->GetMouseY_Impl(); 
    }
}
