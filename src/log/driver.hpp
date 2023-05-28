#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

namespace engine::log
{
    class Entry;

    class IDriver
    {
        public:
            virtual ~IDriver() = default;
            virtual void Submit(const Entry& entry) = 0;
    };
}

#endif
