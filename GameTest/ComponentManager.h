#pragma once
#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include <cassert>
#include <vector>
#include <unordered_map>
#include "Entity.h"
#include "Position.h"
#include "EntityRenderer.h"

// Create a component manager for each "component" (position, rotation, etc) of each entity in the program.
template<typename Component>
class ComponentManager
{
public:
	/* Constructor! */
	ComponentManager(size_t reserved = 0)
	{
		components.reserve(reserved);
		entities.reserve(reserved);
		lookup.reserve(reserved);
	}

	/* Destructor! */
	~ComponentManager() = default;

	/* If there is an entity in this component manager already. */
	bool Contains(Entity entity) const
	{
		return lookup.find(entity) != lookup.end();
	}

	/* Create a component and store it in a vector along with the entity addressed */
	Component& Create(Entity entity)
	{
		// We do not allow invalid ID's here!
		assert(entity != INVALID_ENTITY);
		// Only 1 of this component per entity is allowed.
		assert(lookup.find(entity) == lookup.end());
		assert(entities.size() == components.size());
		assert(lookup.size() == components.size());

		// Updating lookup table.
		lookup[entity] = components.size();

		// Pushing components into vectors.
		components.emplace_back(Component());
		entities.push_back(entity);

		return components.back(); // Returning the component found.
	}

	/* Getting a component reference from the array via an index. */
	Component& operator[] (size_t index)
	{
		return components[index];
	}

	/* Returns the amount of components/entities since they are same size.*/
	size_t GetCount() const
	{
		return components.size();
	}

	/* Gets the entity from the vector based on the index addressed. */
	Entity GetEntity(size_t index) const
	{
		return entities[index];
	}

	/* Returns a pointer to a component if it exists, if not then it return nullptr. */
	Component* GetComponent(Entity entity)
	{
		auto iterator = lookup.find(entity);
		if (iterator != lookup.end()) // If we found the value.
		{
			return &components[iterator->second];
		}
		return nullptr; // If we did not find the value.
	}

	/* Erases the component from the array, as well as the entity. */
	void Erase(Entity entity)
	{
		const auto iterator = lookup.find(entity);

		if (iterator != lookup.end())
		{
			// Grab index
			const size_t index = iterator->second;

			if (index < components.size() - 1)
			{
				// Move dead element to last element, essentially swapping them.
				components[index] = std::move(components.back());
				entities[index] = entities.back();

				lookup[entities[index]] = index;
			}

			components.pop_back();
			entities.pop_back();
			lookup.erase(entity);
		}
	}


	ComponentManager(const ComponentManager&) = delete; // No copying by mistake!
 private:
	// Storing the arrays we need for entities (only 1 component of the same kind for an entity)
	std::vector<Component> components;
	std::vector<Entity> entities;

	// hash map which eliminates the need to iterate through an entire vector.
	std::unordered_map<Entity, size_t> lookup;

};


#endif // !__COMPONENTMANAGER_H__

