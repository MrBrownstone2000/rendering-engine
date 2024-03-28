#ifndef __FRAMETIMER_HPP__
#define __FRAMETIMER_HPP__

#include "../util/types.hpp"

namespace engine
{
    class FrameTimer
    {
    public:
        FrameTimer();

        void tick();
        float dt();

    private:
        uint64_t m_freq;
        uint64_t m_time;
        float m_dt;
    };
}

#endif
