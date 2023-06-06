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

            std::string ToString() const override
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

    class WindowCloseEvent : public Event
    {
        public:
            EVENT_CLASS_CATEGORY(Window)
            EVENT_CLASS_TYPE(WindowClose)
    };
}

#endif
