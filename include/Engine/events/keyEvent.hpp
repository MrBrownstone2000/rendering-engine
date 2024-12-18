#ifndef __KEYEVENT_HPP__
#define __KEYEVENT_HPP__

#include "event.hpp"
#include "../input/keyCodes.hpp"
#include "../util/types.hpp"
#include <sstream>

namespace engine
{
    class KeyEvent : public Event
    {
        public:
            inline KeyCode getKeyCode() const { return m_keyCode; }
            inline u8 getKeyMods() const { return m_mods; }

            EVENT_CLASS_CATEGORY(EventCategory_Keyboard | EventCategory_Input)

        protected:
            KeyEvent(KeyCode keycode, u8 mods) : m_keyCode(keycode), m_mods(mods) {}

            KeyCode m_keyCode;
            u8 m_mods;
    };

    class KeyPressedEvent : public KeyEvent
    {
        public:
            KeyPressedEvent(KeyCode keycode, u8 mods, bool repeated)
                : KeyEvent(keycode, mods), m_repeated(repeated)
            {}

            inline bool isRepeated() const { return m_repeated; }
            std::string toString() const override
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
            KeyReleasedEvent(KeyCode keycode, u8 mods)
                : KeyEvent(keycode, mods)
            {}

            std::string toString() const override
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
            inline const char* getText() const { return m_str; }

            EVENT_CLASS_CATEGORY(EventCategory_Keyboard | EventCategory_Input)
            EVENT_CLASS_TYPE(Text)

        private:
            const char* m_str;
    };
};

#endif
