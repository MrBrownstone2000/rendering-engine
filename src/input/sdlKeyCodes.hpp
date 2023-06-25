#ifndef __SDLKEYCODES_HPP__
#define __SDLKEYCODES_HPP__

#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../util/types.hpp"

namespace engine::input
{
    // SDL to Engine KeyCodes
    MouseButtonType GetMouseButtonType(u8 sdlButton);
    KeyCode GetKeyCode(int sdlKey);

    // Engine to SDL KeyCodes
    u8 GetSDLMouseButton(MouseButtonType button);
    int GetSDLKeyCode(KeyCode key);
    int GetSDLScanCode(KeyCode key);
}

#endif
