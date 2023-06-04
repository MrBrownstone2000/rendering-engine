#ifndef __KEYEVENT_HPP__
#define __KEYEVENT_HPP__

#include "event.hpp"
#include <sstream>

namespace engine::events
{
    class KeyEvent : public Event
    {
        public:
            inline int GetKeyCode() const { return m_keyCode; }

            EVENT_CLASS_CATEGORY(Keyboard | Input)

        protected:
            KeyEvent(int keycode) : m_keyCode(keycode) {}
            int m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
        public:
            KeyPressedEvent(int keycode, bool repeated)
                : KeyEvent(keycode), m_repeated(repeated)
            {}

            inline bool IsRepeated() const { return m_repeated; }
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_keyCode;
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
            KeyReleasedEvent(int keycode)
                : KeyEvent(keycode)
            {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_keyCode;
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyReleased)
    };
};

#endif
