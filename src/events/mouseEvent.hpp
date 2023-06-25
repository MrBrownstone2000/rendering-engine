#ifndef __MOUSEEVENT_HPP__
#define __MOUSEEVENT_HPP__

#include "event.hpp"
#include "../input/keyCodes.hpp"

#include <sstream>
namespace engine::events
{
    class MouseMovedEvent : public Event
    {
        public:
            MouseMovedEvent(int x, int y, int relX, int relY)
                : m_posX(x), m_posY(y), m_relX(relX), m_relY(relY)
            {}

            inline int getX() const { return m_posX; }
            inline int getY() const { return m_posY; }
            inline int relX() const { return m_relX; }
            inline int relY() const { return m_relY; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << m_posX << ", " << m_posY;
                ss << " - " << m_relX << ", " << m_relY;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(Input | Mouse)

        private:
            int m_posX, m_posY;
            int m_relX, m_relY;
    };

    class MouseScrolledEvent : public Event
    {
        public:
            MouseScrolledEvent(float xOffset, float yOffset)
                : m_offsetX(xOffset), m_offsetY(yOffset)
            {}

            inline float getX() const { return m_offsetX; }
            inline float getY() const { return m_offsetY; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: " << m_offsetX << ", " << m_offsetY;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(Input | Mouse)

        private:
            float m_offsetX, m_offsetY;
    };

    class MouseButtonEvent : public Event
    {
        public:
            inline input::MouseButtonType GetMouseButton() const { return m_button; }

            EVENT_CLASS_CATEGORY(Mouse | Input | MouseButton)

        protected:
            MouseButtonEvent(input::MouseButtonType button) : m_button(button) {}
            input::MouseButtonType m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonPressedEvent(input::MouseButtonType button)
                : MouseButtonEvent(button)
            {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonReleasedEvent(input::MouseButtonType button)
                : MouseButtonEvent(button)
            {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}

#endif
