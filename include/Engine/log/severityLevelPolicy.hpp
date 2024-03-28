#ifndef __SEVERITYLEVELPOLICY_HPP__
#define __SEVERITYLEVELPOLICY_HPP__

#include "level.hpp"
#include "policy.hpp"

namespace engine::log
{
    struct Entry;

    class ISeverityLevelPolicy : public IPolicy {};

    class SeverityLevelPolicy : public ISeverityLevelPolicy
    {
        public:
            SeverityLevelPolicy(Level level);
            bool TransformFilter(Entry& entry);

        private:
            Level m_level;
    };
}

#endif
