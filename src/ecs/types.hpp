#ifndef __ECSTYPES_HPP__
#define __ECSTYPES_HPP__

#include "../engine.hpp"
#include "../util/assert.hpp"
#include "../util/exception.hpp"
#include "../util/types.hpp"

namespace engine::ecs
{
    struct Archetype;

    using EntityId = u64;
    constexpr static u32 entityIndexBits = 32;
    constexpr static u32 entityIndexMask = (1l << entityIndexBits) - 1;
    constexpr static u32 entityGenerationBits = 16;
    constexpr static u32 entityGenerationMask = (1l << entityGenerationBits) - 1;

    using ComponentId = EntityId;
    using ArchetypeId = u32;

    constexpr static u32 maxComponents = 256;
    constexpr static u32 maxEntities = (1ul << 32) - 1 - maxComponents;
    constexpr static u32 maxArchetypes = (1ul << 32) - 1;

    M_DEF_EXCEPTION(BadComponent);

    struct ComponentInfo
    {
        ComponentId id;
        size_t size;

        bool operator==(const ComponentInfo& rhs) const
        {
            // If ids are equal, then size should be equal...
            Check(id != rhs.id || size == rhs.size);
            return id == rhs.id && size == rhs.size;
        }
    };

    using Type = std::vector<ComponentInfo>;

    // Stores the information of a particular entity (archetype, data location)
    struct EntityRecord
    {
        std::shared_ptr<Archetype> archetype;
        u32 row; // To index into Archetype::ComponentArray
    };

    // Stores the components information, for a specific archetype
    struct ComponentRecord
    {
        u32 column; //  To index into Archetype::componentsData
    };

    using ArchetypeMap = std::unordered_map<ArchetypeId, ComponentRecord>;
} 

#endif
