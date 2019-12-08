#include "EntityManager.h"
#include <cassert>

namespace AwesomeEngine
{

	EntityManager::EntityManager()
	{
	}

	EntityManager::~EntityManager()
	{
	}


	Entity& EntityManager::CreateEntity()
	{
		// TODO: insert return statement here
		static int entityId = 0;
		mEntities.emplace_back( Entity(entityId++, this) );
		return mEntities.back();
	}

	void EntityManager::DestroyEntity(Entity e)
	{
		
	}

	//const ComponentMask& EntityManager::getComponentMask(Entity e) const
	//{
	//	const auto index = e.getIndex();
	//	assert(index < componentMasks.size());
	//	return componentMasks[index];
	//}


}