#include "pch.hpp"
#include "ecs/entity.hpp"
#include "ecs/world.hpp"

namespace engine::ecs
{
    Entity::Entity(u32 index, u32 generation)
    {
        m_id = (u64(generation) << 32) + index;
        EntityRecord record;
        record.archetype = World::archetypeManager.getDefault();
        record.row = -1;

        World::entityIndex.insert({m_id, record});
    }

    void Entity::remove()
    {
        EntityRecord record = World::entityIndex.at(m_id);
        record.archetype->remove(record.row);
        World::entityIndex.erase(m_id);
        m_id = 0;
    }

    u32 Entity::index() const
    {
        return m_id & entityIndexMask;
    }

    u32 Entity::generation() const
    {
        return (m_id >> entityIndexBits) & entityGenerationMask;
    }

    bool Entity::hasComponent(ComponentId id)
    {
        std::shared_ptr<Archetype> a = World::entityIndex[m_id].archetype;
        const ArchetypeMap& as = World::componentIndex[id];
        return as.count(a->id) != 0;
    }

    void* Entity::get(const ComponentInfo& info)
    {
        const EntityRecord& er = World::entityIndex[m_id];
        std::shared_ptr<Archetype> a = er.archetype;
        ArchetypeMap& cr = World::componentIndex[info.id];
        if (cr.count(a->id) != 0)
        {
            ComponentArray& ca = a->componentsData[cr[a->id].column];
            return ca.get(er.row);
        }
        throw BadComponent("The entity does not have the compnent");
    }

    const void* Entity::get(const ComponentInfo& info) const
    {
        const EntityRecord& er = World::entityIndex[m_id];
        std::shared_ptr<Archetype> a = er.archetype;
        ArchetypeMap& cr = World::componentIndex[info.id];
        if (cr.count(a->id) != 0)
        {
            const ComponentArray& ca = a->componentsData[cr[a->id].column];
            return ca.get(er.row);
        }
        throw BadComponent("The entity does not have the compnent");
    }

        void Entity::add(const ComponentInfo& info, void* data)
        {
            std::shared_ptr<Archetype> oldArchetype = World::entityIndex[m_id].archetype;
            EntityRecord oldRecord = World::entityIndex.at(m_id);

            // Find new archetype, and update the entity record
            std::shared_ptr<Archetype> newArchetype = World::archetypeManager.find(oldArchetype, info, true);
            EntityRecord newRecord;
            newRecord.archetype = newArchetype;
            newRecord.row = newArchetype->componentsData.at(0).size();
            World::entityIndex.at(m_id) = newRecord;

            // Insert row in new archetype
            newArchetype->insertRow();

            // Move old data into new archetype
            for (ComponentInfo oldComponent : oldArchetype->type)
            {
                ArchetypeMap am = World::componentIndex.at(oldComponent.id);
                u32 newArchetypeColumn = am.at(newArchetype->id).column;
                u32 oldArchetypeColumn = am.at(oldArchetype->id).column;

                // Get old component from old ComponentArray
                void* oldComponentData = oldArchetype->componentsData.at(oldArchetypeColumn)
                    .get(oldRecord.row);

                // Set new data
                newArchetype->componentsData.at(newArchetypeColumn).set_back(info.size, oldComponentData);

            }

            // Remove entity from old archetype
            oldArchetype->remove(oldRecord.row);

            // Move new component data
            ArchetypeMap am = World::componentIndex.at(info.id);
            u32 newArchetypeColumn = am.at(newArchetype->id).column;
            newArchetype->componentsData.at(newArchetypeColumn).set_back(info.size, data);
        }

        void Entity::remove(const ComponentInfo& info)
        {
            std::shared_ptr<Archetype> oldArchetype = World::entityIndex[m_id].archetype;
            EntityRecord oldRecord = World::entityIndex.at(m_id);

            // Find new archetype, and update the entity record
            std::shared_ptr<Archetype> newArchetype = World::archetypeManager.find(oldArchetype, info, false);
            EntityRecord newRecord;
            newRecord.archetype = newArchetype;

            if (newArchetype->componentsData.size() > 0)
                newRecord.row = newArchetype->componentsData.at(0).size();

            World::entityIndex.at(m_id) = newRecord;

            // Insert row in new archetype
            newArchetype->insertRow();

            // Move old data into new archetype
            for (ComponentInfo oldComponent : newArchetype->type)
            {
                ArchetypeMap am = World::componentIndex.at(oldComponent.id);
                u32 newArchetypeColumn = am.at(newArchetype->id).column;
                u32 oldArchetypeColumn = am.at(oldArchetype->id).column;

                // Get old component from old ComponentArray
                void* oldComponentData = oldArchetype->componentsData.at(oldArchetypeColumn)
                    .get(oldRecord.row);

                // Set new data
                newArchetype->componentsData.at(newArchetypeColumn).set_back(info.size, oldComponentData);

            }

            // Remove entity from old archetype
            oldArchetype->remove(oldRecord.row);
        }
}
