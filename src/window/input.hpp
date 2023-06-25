#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "../events/keyCodes.hpp"
#include "../events/mouseEvent.hpp"

namespace engine::input
{
    class Input
    {
        public:
            static bool IsKeyPressed(events::KeyCode key)
                { return s_implementation->IsKeyPressed_Impl(key); }
            static bool IsMouseButtonPressed(events::MouseButtonType button)
                { return s_implementation->IsMouseButtonPressed_Impl(button); }
            static float GetMouseX() { return s_implementation->GetMouseX_Impl(); }
            static float GetMouseY() { return s_implementation->GetMouseY_Impl(); }

        protected:
            virtual bool IsKeyPressed_Impl(events::KeyCode key) = 0;
            virtual bool IsMouseButtonPressed_Impl(events::MouseButtonType button) = 0;
            virtual float GetMouseX_Impl() = 0;
            virtual float GetMouseY_Impl() = 0;

        private:
            static Input* s_implementation;
    };
}

#endif
