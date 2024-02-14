#include "pch.hpp"
#include "ecs.hpp"

namespace engine::ecs
{
    // Definition for the extern variables in the ECS system
    std::unordered_map<EntityId, EntityRecord> entityIndex;
    std::unordered_map<ComponentId, ArchetypeMap> componentIndex;
    ArchetypeManager archetypeManager;
}
