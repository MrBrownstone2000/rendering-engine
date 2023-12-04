#ifndef __VIEWPORTEVENT_HPP__
#define __VIEWPORTEVENT_HPP__

#include "event.hpp"
#include "../util/types.hpp"

#include <sstream>

namespace engine
{
    class ImGuiViewport;

    class ViewportResizeEvent : public Event
    {
        public:
            ViewportResizeEvent (const ImGuiViewport* viewport, uint width, uint height)
                : m_width(width), m_height(height), m_viewport(viewport)
            {}

            inline uint getWidth() const { return m_width; }
            inline uint getHeight() const { return m_height; }
            const ImGuiViewport* getViewport() const { return m_viewport; }

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "ViewportResizeEvent : " << m_width << ", " << m_height;
                return ss.str();
            }

            EVENT_CLASS_TYPE(ViewportResize)
            EVENT_CLASS_CATEGORY(EventCategory_Viewport)

        private:
            uint m_width, m_height;
            const ImGuiViewport* m_viewport;
    };
}

#endif
