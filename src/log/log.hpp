#ifndef __LOG_HPP__
#define __LOG_HPP__

#include "entryBuilder.hpp"

namespace engine::log
{
    class IChannel;

    IChannel* GetDefaultChannel();
    void Boot();

#ifdef NDEBUG
    inline constexpr int defaultTraceSkip = 2;
#else
    inline constexpr int defaultTraceSkip = 6;
#endif
}

#define engineLog log::EntryBuilder(__FILE__, __FUNCTION__, __LINE__).chan(log::GetDefaultChannel()).traceSkip(log::defaultTraceSkip)

#endif
