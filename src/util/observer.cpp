#include "pch.hpp"
#include "observer.hpp"

#include <algorithm>

namespace engine::util
{
    Subject::~Subject()
    {
    }

    void Subject::subscribe(IObserver* obs)
    {
        m_observers.push_back(obs);
    }

    void Subject::unsubscribe(IObserver* obs)
    {
        auto it = std::find(m_observers.begin(), m_observers.end(), obs);
        if (it != m_observers.end())
            m_observers.erase(it);
    }

    void Subject::notify()
    {
        for (IObserver* o : m_observers)
            o->onNotify();
    }
}
