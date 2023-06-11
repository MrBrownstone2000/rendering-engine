#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../util/types.hpp"

namespace engine::window::input
{
    events::MouseButtonType GetMouseButtonType(u8 sdlButton);
    events::KeyCode GetKeyCode(int sdlKey);
}

#endif
