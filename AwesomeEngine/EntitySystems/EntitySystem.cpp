#include "EntitySystem.h"
#include <algorithm>

namespace AwesomeEngine
{

	void EntitySystem::addEntity(Entity e)
	{
		entities.push_back(e);
	}

	void EntitySystem::removeEntity(Entity e)
	{
		entities.erase(std::remove_if(entities.begin(), entities.end(),
			[&e](Entity other) { return e == other; }
		), entities.end());
	}

	EntityWorld& EntitySystem::getWorld() const
	{
		assert(world != nullptr);
		return *world;
	}

	
}