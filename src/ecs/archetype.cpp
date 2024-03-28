#include "pch.hpp"
#include "ecs/archetype.hpp"
#include "ecs/world.hpp"

namespace engine::ecs
{
        std::shared_ptr<Archetype> ArchetypeManager::create(const Type& new_type)
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
                World::componentIndex[c.id][new_archetype->id] = ComponentRecord{ i };
            }

            m_archetypes.push_back(new_archetype);


            return new_archetype;
        }
}

