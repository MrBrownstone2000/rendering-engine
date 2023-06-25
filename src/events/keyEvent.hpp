#ifndef __KEYEVENT_HPP__
#define __KEYEVENT_HPP__

#include "event.hpp"
#include "../input/keyCodes.hpp"
#include "../util/types.hpp"
#include <sstream>

namespace engine::events
{
    class KeyEvent : public Event
    {
        public:
            inline input::KeyCode GetKeyCode() const { return m_keyCode; }
            inline u8 GetKeyMods() const { return m_mods; }

            EVENT_CLASS_CATEGORY(Keyboard | Input)

        protected:
            KeyEvent(input::KeyCode keycode, u8 mods) : m_keyCode(keycode), m_mods(mods) {}

            input::KeyCode m_keyCode;
            u8 m_mods;
    };

    class KeyPressedEvent : public KeyEvent
    {
        public:
            KeyPressedEvent(input::KeyCode keycode, u8 mods, bool repeated)
                : KeyEvent(keycode, mods), m_repeated(repeated)
            {}

            inline bool IsRepeated() const { return m_repeated; }
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << int(m_keyCode);
                if (m_repeated)
                    ss << " (repeated)";
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyPressed)

        private:
            bool m_repeated;
    };

    class KeyReleasedEvent : public KeyEvent
    {
        public:
            KeyReleasedEvent(input::KeyCode keycode, u8 mods)
                : KeyEvent(keycode, mods)
            {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << int(m_keyCode);
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyReleased)
    };

    class TextEvent : public Event
    {
        public:
            TextEvent(const char* str) : m_str(str) {}
            inline const char* GetText() const { return m_str; }

            EVENT_CLASS_CATEGORY(Keyboard | Input)
            EVENT_CLASS_TYPE(Text)

        private:
            const char* m_str;
    };
};

#endif
