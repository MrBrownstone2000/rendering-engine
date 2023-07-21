#ifndef __WINDOWEVENT_HPP__
#define __WINDOWEVENT_HPP__

#include "event.hpp"
#include "../util/types.hpp"

#include <sstream>

namespace engine::events
{
    class WindowResizeEvent : public Event
    {
        public:
            WindowResizeEvent(uint width, uint height)
                : m_width(width), m_height(height)
            {}

            inline uint getWidth() const { return m_width; }
            inline uint getHeight() const { return m_height; }

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << m_width << ", " << m_height;
                return ss.str();
            }

            EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(Window)

        private:
            uint m_width, m_height;
    };

    class WindowMovedEvent : public Event
    {
        public:
            WindowMovedEvent(int x, int y)
                : m_x(x), m_y(y)
            {}

            inline int getX() const { return m_x; }
            inline int getY() const { return m_y; }

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "WindowMovedEvent: " << m_x << ", " << m_y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(WindowMoved)
            EVENT_CLASS_CATEGORY(Window)

        private:
            int m_x, m_y;
    };

    class WindowCloseEvent : public Event
    {
        public:
            EVENT_CLASS_CATEGORY(Window)
            EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowFocusEvent : public Event
    {
        public:
            EVENT_CLASS_CATEGORY(Window)
            EVENT_CLASS_TYPE(WindowFocus)
    };

    class WindowLostFocusEvent : public Event
    {
        public:
            EVENT_CLASS_CATEGORY(Window)
            EVENT_CLASS_TYPE(WindowLostFocus)
    };
}

#endif
