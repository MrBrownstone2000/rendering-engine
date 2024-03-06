#include "pch.hpp"
#include "ecs.hpp"
#include "world.hpp"

namespace engine::ecs
{
    std::unordered_map<EntityId, EntityRecord> World::entityIndex;
    std::unordered_map<ComponentId, ArchetypeMap> World::componentIndex;
    ArchetypeManager World::archetypeManager;
}
