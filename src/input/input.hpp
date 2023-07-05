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

    class IInput
    {
        public:
            virtual bool IsKeyPressed(KeyCode key) = 0;
            virtual bool IsMouseButtonPressed(MouseButtonType button) = 0;
            virtual float GetMouseX() = 0;
            virtual float GetMouseY() = 0;
    };
}

#endif
