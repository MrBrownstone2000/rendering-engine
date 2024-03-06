#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "types.hpp"
#include "archetype.hpp"

namespace engine::ecs
{
    // TODO: World should not be a singleton (see flecs api for inspiration)
    //          World::entity();
    //          World::destroy(Entity&);
    // TODO: Test EntityManager
    // TODO: Reuse component space in Archetype
    //       remove entity ? 
    // TODO: Component == Entity ??
    struct World
    {
        static std::unordered_map<EntityId, EntityRecord> entityIndex;
        static std::unordered_map<ComponentId, ArchetypeMap> componentIndex;
        static ArchetypeManager archetypeManager;

        static void clear()
        {
            entityIndex.clear();
            componentIndex.clear();
            archetypeManager = ArchetypeManager();
        }
    };
}

#endif
