#ifndef __SDLINPUT_HPP__
#define __SDLINPUT_HPP__

#include "input.hpp"
#include "keyCodes.hpp"
#include "../util/types.hpp"

namespace engine::input
{
    class SDLInput : public IInput
    {
        public:
            SDLInput();

        public:
            bool IsKeyPressed(KeyCode key) override;
            bool IsMouseButtonPressed(MouseButtonType button) override;
            float GetMouseX() override;
            float GetMouseY() override;

        private:
            const u8* m_keyStates;
    };
}

#endif
