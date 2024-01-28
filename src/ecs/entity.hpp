#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "../util/assert.hpp"
#include "../engine.hpp"
#include "../util/types.hpp"

#include "types.hpp"
#include "archetype.hpp"
#include "component.hpp"

namespace engine::ecs
{
    struct Archetype;

    // TODO: reuse Ids
    class EntityIdGenerator
    {
    public:
        static EntityId get()
        {
            static EntityId val = maxComponents;
            if (val >= maxEntities)
                engineLog.fatal("Entity id limit exceeded");
            return val++;
        }
    };

    class Entity
    {
    public:
        Entity()
        {
            m_id = EntityIdGenerator::get();
            EntityRecord record;
            record.archetype = archetypeManager.getDefault();
            record.row = -1;

            entityIndex.insert({m_id, record});
        }

        ~Entity()
        {
            if (m_id)
                remove();
        }

        // Deletes entity from the world
        void remove()
        {
            EntityRecord record = entityIndex.at(m_id);
            record.archetype->remove(record.row);
            entityIndex.erase(m_id);
            m_id = 0;
        }

        // O(1) average
        template <class Component>
        bool hasComponent()
        {
            ComponentId c = ComponentIdGenerator::get<Component>();
            std::shared_ptr<Archetype> a = entityIndex[m_id].archetype;
            const ArchetypeMap& as = componentIndex[c];
            return as.count(a->id) != 0;
        }

        // O(1) average
        template <typename Component>
        Component& get()
        {
            const ComponentId c = ComponentIdGenerator::get<Component>();
            const EntityRecord& er = entityIndex[m_id];
            std::shared_ptr<Archetype> a = er.archetype;
            ArchetypeMap& cr = componentIndex[c];
            if (cr.count(a->id) != 0)
            {
                ComponentArray& ca = a->componentsData[cr[a->id].column];
                return ca.at<Component>(er.row);
            }
            throw BadComponent("The entity does not have the compnent");
        }

        // O(1) average
        template <typename Component>
        const Component& get() const
        {
            const ComponentId c = ComponentIdGenerator::get<Component>();
            const EntityRecord& er = entityIndex[m_id];
            std::shared_ptr<Archetype> a = er.archetype;
            ArchetypeMap& cr = componentIndex[c];
            if (cr.count(a->id) != 0)
            {
                const ComponentArray& ca = a->componentsData[cr[a->id].column];
                return ca.at<Component>(er.row);
            }
            throw BadComponent("The entity does not have the compnent");
        }

        template <typename Component>
        void add(const Component& component)
        {
            Assert(!hasComponent<Component>());
            const ComponentInfo c = { 
                .id = ComponentIdGenerator::get<Component>(),
                .size = sizeof(Component)
            };
            std::shared_ptr<Archetype> oldArchetype = entityIndex[m_id].archetype;
            EntityRecord oldRecord = entityIndex.at(m_id);

            // Find new archetype, and update the entity record
            std::shared_ptr<Archetype> newArchetype = archetypeManager.find(oldArchetype, c, true);
            EntityRecord newRecord;
            newRecord.archetype = newArchetype;
            newRecord.row = newArchetype->componentsData.at(0).size();
            entityIndex.at(m_id) = newRecord;

            // Insert row in new archetype
            newArchetype->insertRow();

            // Move old data into new archetype
            for (ComponentInfo oldComponent : oldArchetype->type)
            {
                ArchetypeMap am = componentIndex.at(oldComponent.id);
                u32 newArchetypeColumn = am.at(newArchetype->id).column;
                u32 oldArchetypeColumn = am.at(oldArchetype->id).column;

                // Get old component from old ComponentArray
                void* oldComponentData = oldArchetype->componentsData.at(oldArchetypeColumn)
                    .get(oldRecord.row);

                // Set new data
                newArchetype->componentsData.at(newArchetypeColumn).set_back(sizeof(Component), oldComponentData);

            }

            // Remove entity from old archetype
            oldArchetype->remove(oldRecord.row);

            // Move new component data
            ArchetypeMap am = componentIndex.at(c.id);
            u32 newArchetypeColumn = am.at(newArchetype->id).column;
            newArchetype->componentsData.at(newArchetypeColumn).set_back(sizeof(Component), &component);
        }

        template <typename Component>
        void remove()
        {
            Assert(hasComponent<Component>());
            const ComponentInfo c = { 
                .id = ComponentIdGenerator::get<Component>(),
                .size = sizeof(Component)
            };
            std::shared_ptr<Archetype> oldArchetype = entityIndex[m_id].archetype;
            EntityRecord oldRecord = entityIndex.at(m_id);

            // Find new archetype, and update the entity record
            std::shared_ptr<Archetype> newArchetype = archetypeManager.find(oldArchetype, c, false);
            EntityRecord newRecord;
            newRecord.archetype = newArchetype;

            if (newArchetype->componentsData.size() > 0)
                newRecord.row = newArchetype->componentsData.at(0).size();

            entityIndex.at(m_id) = newRecord;

            // Insert row in new archetype
            newArchetype->insertRow();

            // Move old data into new archetype
            for (ComponentInfo oldComponent : newArchetype->type)
            {
                ArchetypeMap am = componentIndex.at(oldComponent.id);
                u32 newArchetypeColumn = am.at(newArchetype->id).column;
                u32 oldArchetypeColumn = am.at(oldArchetype->id).column;

                // Get old component from old ComponentArray
                void* oldComponentData = oldArchetype->componentsData.at(oldArchetypeColumn)
                    .get(oldRecord.row);

                // Set new data
                newArchetype->componentsData.at(newArchetypeColumn).set_back(sizeof(Component), oldComponentData);

            }

            // Remove entity from old archetype
            oldArchetype->remove(oldRecord.row);
        }

    private:
        EntityId m_id;
    };
};

#endif
