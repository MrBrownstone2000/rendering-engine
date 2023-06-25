#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../util/types.hpp"

namespace engine::window::input
{
    // SDL to engine KeyCodes
    events::MouseButtonType GetMouseButtonType(u8 sdlButton);
    events::KeyCode GetKeyCode(int sdlKey);

    // Engine to SDL KeyCodes
    u8 GetSDLMouseButton(events::MouseButtonType button);
    int GetSDLKeyCode(events::KeyCode key);
}

#endif
