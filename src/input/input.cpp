#include "pch.hpp"
#include "input.hpp"
#include "sdlKeyCodes.hpp"

#include <SDL.h>

namespace engine::input
{
    namespace
    {
        int m_mouseOffsetX;
        int m_mouseOffsetY;

        const u8* m_keyStates;
    }

    void Boot()
    {
        m_keyStates = SDL_GetKeyboardState(nullptr);
    }

    bool IsKeyPressed(KeyCode key)
    { 
        return m_keyStates[SDL_GetScancodeFromKey(GetSDLKeyCode(key))];
    }

    bool IsMouseButtonPressed(MouseButtonType button)
    {
        int sdl_buttons = SDL_GetMouseState(nullptr, nullptr);
        return sdl_buttons & SDL_BUTTON(GetSDLMouseButton(button));
    }

    float GetMouseX()
    {
        int x;
        SDL_GetMouseState(&x, nullptr);
        return x;
    }

    float GetMouseY() 
    { 
        int y;
        SDL_GetMouseState(nullptr, &y);
        return y;
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
