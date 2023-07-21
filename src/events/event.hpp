#ifndef __EVENTS_HPP__
#define __EVENTS_HPP__

#include "../util/macros.hpp"

#include <string>

namespace engine::events
{
    enum class EventType
    {
        None,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, Text,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    };

    enum EventCategory
    {
        None        = 0,
        Input       = M_BIT(0),
        Keyboard    = M_BIT(1),
        Mouse       = M_BIT(2),
        MouseButton = M_BIT(3),
        Window      = M_BIT(4),
    };

#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType getType() const override { return GetStaticType(); } \
    virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int getCategories() const override { return category; }

    class Event
    {
        friend class EventDispatcher;
        public:
            virtual EventType getType() const = 0;
            virtual const char* getName() const = 0;
            virtual int getCategories() const = 0;
            virtual std::string toString() const { return getName(); }

            inline bool isInCategory(EventCategory cat)
            {
                return getCategories() & cat;
            }

            operator std::string() { return toString(); }
            bool isHandled() const { return m_handled; }

        protected:
            bool m_handled = false;
    };
    
    inline std::ostream& operator<<(std::ostream& os, Event& event)
    {
        return os << event.toString();
    }
}

#endif
