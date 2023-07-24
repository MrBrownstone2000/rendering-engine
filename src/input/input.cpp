#include "pch.hpp"
#include "input.hpp"
#include "sdlInput.hpp"

#include "ioc/singleton.hpp"

namespace engine::input
{
    namespace
    {
        int m_mouseOffsetX;
        int m_mouseOffsetY;
    }

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

    void SetMouseOffset(int x, int y)
    {
        m_mouseOffsetX = x;
        m_mouseOffsetY = y;
    }

    int GetMouseOffsetX()
    {
        return m_mouseOffsetX;
    }

    int GetMouseOffsetY()
    {
        return m_mouseOffsetY;
    }
}
