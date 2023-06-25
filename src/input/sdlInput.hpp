#ifndef __SDLINPUT_HPP__
#define __SDLINPUT_HPP__

#include "input.hpp"
#include "keyCodes.hpp"
#include "../util/types.hpp"

namespace engine::input
{
    class SDLInput : public Input
    {
        public:
            SDLInput();

        private:
            bool IsKeyPressed_Impl(KeyCode key) override;
            bool IsMouseButtonPressed_Impl(MouseButtonType button) override;
            float GetMouseX_Impl() override;
            float GetMouseY_Impl() override;

        private:
            const u8* m_keyStates;
    };
}

#endif
