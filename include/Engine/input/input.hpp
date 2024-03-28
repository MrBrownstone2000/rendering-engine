#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "keyCodes.hpp"

namespace engine
{
    namespace input
    {
        void Boot();

        bool IsKeyPressed(KeyCode key);
        bool IsMouseButtonPressed(MouseButtonType button);
        float GetMouseX();
        float GetMouseY();

        void SetMouseOffset(int x, int y);
        int GetMouseOffsetX();
        int GetMouseOffsetY();
    }
}

#endif
