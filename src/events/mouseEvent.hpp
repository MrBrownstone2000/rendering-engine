#ifndef __MOUSEEVENT_HPP__
#define __MOUSEEVENT_HPP__

#include "event.hpp"
#include <sstream>
namespace engine::events
{
    class MouseMovedEvent : public Event
    {
        public:
            MouseMovedEvent(float x, float y)
                : m_posX(x), m_posY(y)
            {}

            inline float getX() const { return m_posX; }
            inline float getY() const { return m_posY; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << m_posX << ", " << m_posY;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(Input | Mouse)

        private:
            float m_posX, m_posY;
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
            inline int GetMouseButton() const { return m_button; }

            EVENT_CLASS_CATEGORY(Mouse | Input | MouseButton)

        protected:
            MouseButtonEvent(int button) : m_button(button) {}
            int m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonPressedEvent(int button)
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
            MouseButtonReleasedEvent(int button)
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