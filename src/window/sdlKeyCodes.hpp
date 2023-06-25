#ifndef __SDLKEYCODES_HPP__
#define __SDLKEYCODES_HPP__

#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../util/types.hpp"

namespace engine::input
{
    // SDL to engine KeyCodes
    events::MouseButtonType GetMouseButtonType(u8 sdlButton);
    events::KeyCode GetKeyCode(int sdlKey);

    // Engine to SDL KeyCodes
    u8 GetSDLMouseButton(events::MouseButtonType button);
    int GetSDLKeyCode(events::KeyCode key);
    int GetSDLScanCode(events::KeyCode key);
}

#endif
