#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include "../util/assert.hpp"
#include "../engine.hpp"
#include "../util/types.hpp"

#include "types.hpp"
#include "archetype.hpp"

namespace engine::ecs
{
    // TODO: Component == Entity
    class ComponentIdGenerator
    {
    public:
        template <class T>
        static ComponentId get()
        {
            const static u32 id = generate();
            return id;
        }

    private:
        static ComponentId generate()
        {
            static ComponentId val = 1;
            if (val >= maxComponents)
                engineLog.fatal("Component limit exceeded");
            return val++;
        }
    };
}

#endif
