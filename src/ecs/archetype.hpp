#ifndef __ARCHETYPE_HPP__
#define __ARCHETYPE_HPP__

#include <iostream>
#include <unordered_set>

#include "../engine.hpp"
#include "../util/assert.hpp"
#include "../util/types.hpp"

#include "componentArray.hpp"
#include "types.hpp"

namespace engine::ecs
{
    class ArchetypeIdGenerator
    {
    public:
        static ArchetypeId get()
        {
            static u32 val = 0;
            if (val >= maxArchetypes)
            {
                std::cerr << "Archetype id limit exceeded" << std::endl;
                exit(1);
            }

            return val++;
        }
    };

    using ArchetypeSet = std::unordered_set<ArchetypeId>;

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
}

#endif
