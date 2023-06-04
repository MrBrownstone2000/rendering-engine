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
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    };

    enum EventCategory
    {
        None        = 0,
        Input       = M_BIT(0),
        Keyboard    = M_BIT(1),
        Mouse       = M_BIT(2),
        MouseButton = M_BIT(3),
    };

#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategories() const override { return category; }

    class Event
    {
        friend class EventDispatcher;
        public:
            virtual EventType GetType() const = 0;
            virtual const char* GetName() const = 0;
            virtual int GetCategories() const = 0;
            virtual std::string ToString() const { return GetName(); }

            inline bool IsInCategory(EventCategory cat)
            {
                return GetCategories() & cat;
            }

            operator std::string() { return ToString(); }

        protected:
            bool m_handled = false;
    };
    
    inline std::ostream& operator<<(std::ostream& os, Event& event)
    {
        return os << event.ToString();
    }
}

#endif
