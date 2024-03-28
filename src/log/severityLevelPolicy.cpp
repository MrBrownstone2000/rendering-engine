#include "pch.hpp"
#include "log/severityLevelPolicy.hpp"

#include "log/entry.hpp"

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
