#ifndef __POLICY_HPP__
#define __POLICY_HPP__

namespace engine::log
{
    struct Entry;

    class IPolicy
    {
        public:
            virtual ~IPolicy() = default;
            virtual bool TransformFilter(Entry&) = 0;
    };
}

#endif
