#ifndef __EVENTDISPATCHER_HPP__
#define __EVENTDISPATCHER_HPP__

#include "event.hpp"
#include <functional>

namespace engine
{
    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T&)>;

        public:
            EventDispatcher(Event& event)
                : m_event(event)
            {}

            template <typename T>
            bool dispatch(EventFn<T> function)
            {
                if (m_event.getType() == T::GetStaticType())
                {
                    m_event.m_handled = function(*(T*)&m_event);
                    return true;
                }
                return false;
            }

        private:
            Event& m_event;
    };
}

#endif
