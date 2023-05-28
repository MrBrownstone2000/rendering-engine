#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

namespace engine::log
{
    struct Entry;

    class IChannel
    {
        public:
            virtual void Submit(Entry&) = 0;
    };
}

#endif
