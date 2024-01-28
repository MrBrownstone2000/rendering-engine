#ifndef __ECS_HPP__
#define __ECS_HPP__

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../engine.hpp"
#include "../util/types.hpp"
#include "../util/exception.hpp"

namespace engine::ecs
{
    using EntityId = u64;
    using ComponentId = EntityId;

    M_DEF_EXCEPTION(BadComponent);

    struct ComponentInfo
    {
        ComponentId id;
        size_t size;

        bool operator==(const ComponentInfo& rhs) const
        {
            // TODO: remove check ?
            // (If ids are equal, then size should be equal...)
            return id == rhs.id && size == rhs.size;
        }
    };

    using Type = std::vector<ComponentInfo>;

    // Array of Components Data.
    // Uses type erasure to store the data
    class ComponentArray
    {
    public:
        ComponentArray(size_t initialSize = 1024)
            : m_data(nullptr), m_size(0), m_maxSize(initialSize), m_elementSize(0)
        {
        }

        ~ComponentArray()
        {
            if (m_data)
                free(m_data);
        }

        size_t getElementSize()
        {
            return m_elementSize;
        }

        template<class T>
        T& at(size_t i)
        {
            Check(m_data);
            Check(m_elementSize == sizeof(T));
            Check(i < m_size);
            return ((T*) m_data)[i];
        }

        template<class T>
        const T& at(size_t i) const
        {
            Check(m_data);
            Check(m_elementSize == sizeof(T));
            Check(i < m_size);
            return ((T*) m_data)[i];
        }

        void* get(size_t i, size_t size)
        {
            // TODO: size param redundant...
            Check(m_data);
            Check(m_elementSize == size);
            Check(i < m_size);
            return m_data + m_elementSize * i;
        }

        void set_back(size_t size, const void* data)
        {
            Check(m_data);
            Check(m_elementSize);
            memcpy(m_data + (m_size - 1) * m_elementSize, data, size);
        }

        template<class T>
        void push_back(T&& elt)
        {
            using EltType = std::remove_reference<T>::type;
            
            if (!m_data)
                setup(sizeof(T));
            else
                Check(m_elementSize == sizeof(T));

            insertEmpty();
            ((EltType*) m_data)[m_size - 1] = std::move(elt);
        }

        void insertEmpty()
        {
            Check(m_data);

            if (m_size >= m_maxSize)
            {
                char* new_array = (char*) malloc(2 * m_maxSize * m_elementSize);
                memcpy(new_array, m_data, m_maxSize * m_elementSize);
                m_maxSize *= 2;
                free(m_data);
                m_data = new_array;
            }

            m_size++;
        }

        void erase(size_t i)
        {
            Check(m_data);
            Check(i < m_size);
            m_size--;
            if (m_size - i > 1)
            {
                void* elt = m_data + m_elementSize * i;
                void* nextElt = (char*) elt + m_elementSize;
                memmove(elt, nextElt, (m_size - i) * m_elementSize);
            }
        }

        size_t size() const
        {
            return m_size;
        }

        void setup(size_t elementSize)
        {
            m_data = (char*) malloc(m_maxSize * elementSize);
            m_elementSize = elementSize;
        }

    private:
        char* m_data;
        u64 m_size;
        u64 m_maxSize;
        u64 m_elementSize;
    };

    static constexpr u32 maxComponents = 256;

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
            static ComponentId val = 0;
            if (val >= maxComponents)
                engineLog.fatal("Component limit exceeded");
            return val++;
        }
    };

    constexpr static u32 maxEntities = (1ul << 32) - 1 - maxComponents;

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

    struct Archetype;

    // Stores the information of a particular entity (archetype, data location)
    struct EntityRecord
    {
        std::shared_ptr<Archetype> archetype;
        u32 row; // To index into Archetype::ComponentArray
    };

    // Used to get the information for an entity
    extern std::unordered_map<EntityId, EntityRecord> entityIndex;

    using ArchetypeId = u32;
    class ArchetypeIdGenerator
    {
    public:
        static ArchetypeId get()
        {
            static u32 val = 0;
            if (val >= maxEntities)
            {
                std::cerr << "Archetype id limit exceeded" << std::endl;
                exit(1);
            }

            return val++;
        }
    };

    using ArchetypeSet = std::unordered_set<ArchetypeId>;

    // Stores the components information, for a specific archetype
    struct ComponentRecord
    {
        u32 column; //  To index into Archetype::componentsData
    };

    using ArchetypeMap = std::unordered_map<ArchetypeId, ComponentRecord>;

    extern std::unordered_map<ComponentId, ArchetypeMap> componentIndex;

    struct ArchetypeGraphEdge;

    // Archetype
    // Stores the structure of arrays of its entites
    struct Archetype
    {
        ArchetypeId id;
        Type type;
        std::vector<ComponentArray> componentsData;
        std::unordered_map<ComponentId, ArchetypeGraphEdge> neighbors;

        // Makes room for a new entity
        void insertRow()
        {
            for (ComponentArray& ca : componentsData)
                ca.insertEmpty();
        }

        void remove(size_t row)
        {
            // TODO: handle this... 
            // Can't erase elements without adjusting their entityRecords...
            // Need to ensure the rows stay packed with "live" data

            // for (ComponentArray& ca : componentsData)
            // {
            //     Check(row < ca.size());
            //     ca.erase(row);
            // }
        }
    };

    struct ArchetypeGraphEdge
    {
        std::shared_ptr<Archetype> add;
        std::shared_ptr<Archetype> remove;
    };

    class ArchetypeManager
    {
    public:
        ArchetypeManager()
        {
            std::shared_ptr<Archetype> a = std::make_shared<Archetype>();
            a->id = ArchetypeIdGenerator::get();
            m_archetypes.push_back(a);
        }

        std::shared_ptr<Archetype> find(std::shared_ptr<Archetype> oldArchetype, ComponentInfo newComponent, bool add = true)
        {
            // Find archetype in the graph
            if (oldArchetype->neighbors.count(newComponent.id) > 0)
            {
                const ArchetypeGraphEdge& e = oldArchetype->neighbors.at(newComponent.id);
                if (add)
                    return e.add;
                else
                    return e.remove;
            }

            // Find archetype if it exists (but is not in the graph)
            Type new_type = oldArchetype->type;
            if (add)
                new_type.push_back(newComponent);
            else
                std::erase(new_type, newComponent);
            for (auto currentArchetype : m_archetypes)
            {
                if (currentArchetype->type == new_type)
                {
                    if (add)
                    {
                        oldArchetype->neighbors[newComponent.id].add = currentArchetype;
                        currentArchetype->neighbors[newComponent.id].remove = oldArchetype;
                    }
                    else
                    {
                        oldArchetype->neighbors[newComponent.id].remove = currentArchetype;
                        currentArchetype->neighbors[newComponent.id].add = oldArchetype;
                    }
                    return currentArchetype;
                }
            }

            // Create Archetype otherwise
            std::shared_ptr<Archetype> new_archetype = create(new_type);
            if (add)
            {
                oldArchetype->neighbors[newComponent.id].add = new_archetype;
                new_archetype->neighbors[newComponent.id].remove = oldArchetype;
            }
            else
            {
                oldArchetype->neighbors[newComponent.id].remove = new_archetype;
                new_archetype->neighbors[newComponent.id].add = oldArchetype;
            }

            return new_archetype;
        }

        std::shared_ptr<Archetype> create(const Type& new_type)
        {
            std::shared_ptr<Archetype> new_archetype = std::make_shared<Archetype>();
            new_archetype->id = ArchetypeIdGenerator::get();
            new_archetype->type = new_type;

            // Init components array
            new_archetype->componentsData.resize(new_type.size());

            // Setup the components  array, and
            // Update componentIndex
            for (u32 i = 0; i < new_type.size(); ++i)
            {
                ComponentInfo c = new_type.at(i); 
                new_archetype->componentsData[i].setup(c.size);
                componentIndex[c.id][new_archetype->id] = ComponentRecord{ i };
            }

            m_archetypes.push_back(new_archetype);


            return new_archetype;
        }

        std::shared_ptr<Archetype> getDefault()
        {
            Check(m_archetypes.size() > 0);
            return m_archetypes[0];
        }

    private:
        std::vector<std::shared_ptr<Archetype>> m_archetypes;
    };

    extern ArchetypeManager archetypeManager;

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
            // TODO: remove entity
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
                    .get(oldRecord.row, oldComponent.size);

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
                    .get(oldRecord.row, oldComponent.size);

                // Set new data
                newArchetype->componentsData.at(newArchetypeColumn).set_back(sizeof(Component), oldComponentData);

            }

            // Remove entity from old archetype
            oldArchetype->remove(oldRecord.row);
        }


    private:
        EntityId m_id;
    };
}

#endif
