#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

#include <vector>

namespace engine::util
{
    class IObserver
    {
        public:
            virtual ~IObserver() = default;
            virtual void onNotify() = 0;
    };

    class Subject
    {
        public:
            virtual ~Subject() = 0;
            void subscribe(IObserver* obs);
            void unsubscribe(IObserver* obs);

        protected:
            void notify();

        private:
            std::vector<IObserver*> m_observers;
    };
}

#endif
