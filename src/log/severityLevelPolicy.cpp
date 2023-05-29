#ifndef __SEVERITYLEVELPOLICY_CPP__
#define __SEVERITYLEVELPOLICY_CPP__

#include "severityLevelPolicy.hpp"
#include "entry.hpp"

namespace engine::log
{
    SeverityLevelPolicy::SeverityLevelPolicy(Level level)
        : m_level(level)
    {
    }

    bool SeverityLevelPolicy::TransformFilter(Entry& entry)
    {
        return entry.m_level <= m_level;
    }
}

#endif
