#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "keyCodes.hpp"

namespace engine::input
{
    void Boot();

    class Input
    {
        public:
            static bool IsKeyPressed(KeyCode key);
            static bool IsMouseButtonPressed(MouseButtonType button);
            static float GetMouseX();
            static float GetMouseY();

            static Input* GetDefault();

        protected:
            virtual bool IsKeyPressed_Impl(KeyCode key) = 0;
            virtual bool IsMouseButtonPressed_Impl(MouseButtonType button) = 0;
            virtual float GetMouseX_Impl() = 0;
            virtual float GetMouseY_Impl() = 0;
    };
}

#endif
