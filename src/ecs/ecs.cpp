#include "pch.hpp"
#include "ecs.hpp"

namespace engine::ecs
{
    std::unordered_map<EntityId, EntityRecord> entityIndex;

    std::unordered_map<ComponentId, ArchetypeMap> componentIndex;

    ArchetypeManager archetypeManager;
}
