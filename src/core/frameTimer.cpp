#include "pch.hpp"
#include "core/frameTimer.hpp"

#include <SDL.h>

namespace engine
{
    FrameTimer::FrameTimer()
    {
        m_time = SDL_GetPerformanceCounter();
        m_freq = SDL_GetPerformanceFrequency();
    }

    void FrameTimer::tick()
    {
       uint64_t prev = m_time;
       m_time = SDL_GetPerformanceCounter();
       m_dt = double(m_time - prev) / m_freq;
    }

    float FrameTimer::dt()
    {
        return m_dt;
    }
}
