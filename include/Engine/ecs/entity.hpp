#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <deque>

#include "../util/assert.hpp"
#include "../engine.hpp"
#include "../util/types.hpp"

#include "types.hpp"
#include "archetype.hpp"
#include "component.hpp"

namespace engine::ecs
{
    struct Archetype;

    class Entity
    {
    public:
        Entity(u32 index, u32 generation);

        // Deletes entity from the world
        void remove();

        u32 index() const;
        u32 generation() const;

        // O(1) average
        template <class Component>
        bool hasComponent()
        {
            ComponentId c = ComponentIdGenerator::get<Component>();
            return hasComponent(c);
        }

        // O(1) average
        template <typename Component>
        Component& get()
        {
            const ComponentInfo c = { 
                .id = ComponentIdGenerator::get<Component>(),
                .size = sizeof(Component)
            };

            return *(static_cast<Component*>(get(c)));
        }

        // O(1) average
        template <typename Component>
        const Component& get() const
        {
            const ComponentInfo c = { 
                .id = ComponentIdGenerator::get<Component>(),
                .size = sizeof(Component)
            };
            return *(static_cast<const Component*>(get(c)));
        }

        template <typename Component>
        void add(const Component& component)
        {
            Assert(!hasComponent<Component>());
            const ComponentInfo c = { 
                .id = ComponentIdGenerator::get<Component>(),
                .size = sizeof(Component)
            };

            add(c, (void*) &component);
        }

        template <typename Component>
        void remove()
        {
            Assert(hasComponent<Component>());
            const ComponentInfo c = { 
                .id = ComponentIdGenerator::get<Component>(),
                .size = sizeof(Component)
            };

            remove(c);
        }

    private:
        bool hasComponent(ComponentId id);

        void* get(const ComponentInfo& info);
        const void* get(const ComponentInfo& info) const;

        void add(const ComponentInfo& info, void* data);
        void remove(const ComponentInfo& info);

    private:
        EntityId m_id;
    };

    // TODO: reuse Ids
    // see bitsquid blogspot (stingray engine)
    class EntityManager
    {
    private:
        EntityManager()
            : m_currentIndex(maxComponents)
        {
        }

        EntityId generateIndex()
        {
            if (m_currentIndex >= maxEntities)
                engineLog.fatal("Entity id limit exceeded");
            return m_currentIndex++;
        }

        Entity create()
        {
            u32 index;
            u16 generation;
            if (m_freeIndices.size())
            {
                index = m_freeIndices.front();
                generation = m_generations[index];
                m_freeIndices.pop_front();
            }
            else 
            {
                index = m_generations.size();
                generation = 0;
                m_generations.push_back(0);
                Check(index <= entityIndexMask);
            }
            return Entity(index, generation);
        }

        bool alive(Entity e)
        {
            return m_generations[e.index()] == e.generation();
        }

        void destroy(Entity e)
        {
            u32 index = e.index();
            m_generations[index]++;
            m_freeIndices.push_back(index);
        }

    private:
        std::deque<u32> m_freeIndices; // Free indices to be reused
        std::vector<u16> m_generations; // Current generation number for each entity index
        EntityId m_currentIndex; // Last used index (used for index generation)
    };
};

#endif
