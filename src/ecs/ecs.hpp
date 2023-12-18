#ifndef __ECS_HPP__
#define __ECS_HPP__

#include <cstdlib>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../engine.hpp"
#include "../util/types.hpp"

namespace engine::ecs
{
    using EntityId = u64;
    using ComponentId = EntityId;

    using Type = std::vector<ComponentId>;

    class ComponentArray
    {
    public:
        ComponentArray(u64 element_size, u64 initial_size = 1024)
            : m_size(0), m_max_size(initial_size), m_element_size(element_size)
        {
            m_data = malloc(initial_size * element_size);
        }

        ~ComponentArray()
        {
            free(m_data);
        }

        template<class T>
        T& at(size_t i)
        {
            return ((T*) m_data)[i];
        }

        template<class T>
        const T& at(size_t i) const
        {
            return ((T*) m_data)[i];
        }

        template<class T>
        void push_back(T&& elt)
        {
            using Type = std::remove_reference<T>::type;

            if (m_size >= m_max_size)
            {
                void* new_array = malloc(2 * m_max_size * m_element_size);
                memcpy(new_array, m_data, m_max_size * m_element_size);
                m_max_size *= 2;
                free(m_data);
                m_data = new_array;
            }

            ((Type*) m_data)[m_size] = std::move(elt);
            m_size++;
        }

        size_t size() const
        {
            return m_size;
        }

    private:
        void* m_data;
        u64 m_size;
        u64 m_max_size;
        u64 m_element_size;
    };

    static constexpr u32 maxComponents = 256;

    class ComponentIdGenerator
    {
    public:
        template <class T>
        static ComponentId get()
        {
            static u32 id = generate();
            return id;
        }

    private:
        static ComponentId generate()
        {
            static ComponentId val = 0;
            if (val >= maxComponents)
                engineLog.fatal("Component limit exceeded");
            return val++;
        }
    };

    static constexpr u32 maxEntities = (1ul << 32) - 1 - maxComponents;

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

    using ArchetypeId = u32;
    class ArcheypeIdGenerator
    {
    public:
        static ArchetypeId get()
        {
            static u32 val = maxComponents;
            if (val >= maxEntities)
                engineLog.fatal("Entity id limit exceeded");
            return val++;
        }
    };

    struct ArchetypeGraphEdge;

    struct Archetype
    {
        ArchetypeId id;
        Type type;
        std::vector<ComponentArray> componentsData;
        std::unordered_map<ComponentId, ArchetypeGraphEdge> neighbors;
    };

    struct ArchetypeGraphEdge
    {
        Archetype add;
        Archetype remove;
    };

    Archetype& find(const Archetype& a, ComponentId c, bool add = true)
    {
        if (a.neighbors.count(c) > 0)
        {
            ArchetypeGraphEdge& e = a.neighbors[c];
        }
    }

    struct EntityRecord
    {
        Archetype archetype;
        u32 row;
    };

    static std::unordered_map<EntityId, EntityRecord> entityIndex;

    using ArchetypeSet = std::unordered_set<ArchetypeId>;

    struct ComponentRecord
    {
        ArchetypeSet archetypeSet;
        u32 column;
    };

    static std::unordered_map<ComponentId, ComponentRecord> componentIndex;

    class Entity
    {
    public:
        Entity()
        {
            m_id = EntityIdGenerator::get();
        }

        // O(1) average
        template <class Component>
        bool hasComponent()
        {
            ComponentId c = ComponentIdGenerator::get<Component>();
            const Archetype& a = entityIndex[m_id].archetype;
            const ArchetypeSet& as = componentIndex[c].archetypeSet;
            return as.count(a.id) != 0;
        }

        // O(1) average
        template <typename Component>
        Component&& get()
        {
            const ComponentId c = ComponentIdGenerator::get<Component>();
            const EntityRecord& er = entityIndex[m_id];
            const Archetype& a = er.archetype;
            const ComponentRecord& cr = componentIndex[c];
            const ArchetypeSet& as = cr.archetypeSet;
            if (as.count(a.id) != 0)
            {
                const ComponentArray& ca = a.componentsData[cr.column];
                return ca.at<Component>(er.row);
            }
        }

        template <typename Component>
        void add(Component&& component)
        {
            Assert(!hasComponent<Component>());
            const ComponentId c = ComponentIdGenerator::get<Component>();
            Archetype& a = entityIndex[m_id].archetype;

            // Find new archetype...
            // Use archetype graph...
        }


    private:
        EntityId m_id;
    };
}

#endif
