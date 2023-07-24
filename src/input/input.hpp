#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "keyCodes.hpp"

namespace engine::input
{
    void Boot();

    bool IsKeyPressed(KeyCode key);
    bool IsMouseButtonPressed(MouseButtonType button);
    float GetMouseX();
    float GetMouseY();

    void SetMouseOffset(int x, int y);
    int GetMouseOffsetX();
    int GetMouseOffsetY();

    class IInput
    {
        public:
            virtual bool isKeyPressed(KeyCode key) = 0;
            virtual bool isMouseButtonPressed(MouseButtonType button) = 0;
            virtual float getMouseX() = 0;
            virtual float getMouseY() = 0;
    };
}

#endif
