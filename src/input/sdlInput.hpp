#ifndef __SDLINPUT_HPP__
#define __SDLINPUT_HPP__

#include "input.hpp"
#include "keyCodes.hpp"
#include "../util/types.hpp"

namespace engine
{
    class SDLInput : public IInput
    {
        public:
            SDLInput();

        public:
            bool isKeyPressed(KeyCode key) override;
            bool isMouseButtonPressed(MouseButtonType button) override;
            float getMouseX() override;
            float getMouseY() override;

        private:
            const u8* m_keyStates;
    };
}

#endif
