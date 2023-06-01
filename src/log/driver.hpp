#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include <memory>

namespace engine::log
{
    class Entry;
    class ITextFormatter;

    class IDriver
    {
        public:
            virtual ~IDriver() = default;
            virtual void Submit(const Entry& entry) = 0;
            virtual void Flush() = 0;
    };

    class ITextDriver : public IDriver
    {
        public:
            virtual void Submit(const Entry& entry) = 0;
            virtual void Flush() = 0;
            virtual void SetFormatter(std::shared_ptr<ITextFormatter>) = 0;
    };
}

#endif
