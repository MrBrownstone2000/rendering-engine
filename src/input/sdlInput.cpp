#include "pch.hpp"
#include "sdlInput.hpp"
#include "sdlKeyCodes.hpp"

#include <SDL.h>

namespace engine::input
{
    SDLInput::SDLInput()
    {
        m_keyStates = SDL_GetKeyboardState(nullptr);
    }

    bool SDLInput::IsKeyPressed_Impl(KeyCode key)
    {
        return m_keyStates[GetSDLScanCode(key)];
    }

    bool SDLInput::IsMouseButtonPressed_Impl(MouseButtonType button)
    {
        int sdl_buttons = SDL_GetMouseState(nullptr, nullptr);
        return sdl_buttons & SDL_BUTTON(GetSDLMouseButton(button));
    }

    float SDLInput::GetMouseX_Impl()
    {
        int x;
        SDL_GetMouseState(&x, nullptr);
        return x;
    }

    float SDLInput::GetMouseY_Impl()
    {
        int y;
        SDL_GetMouseState(nullptr, &y);
        return y;
    }
}
