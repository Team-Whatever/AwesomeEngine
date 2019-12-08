#pragma once

#include <vector>
#include "Entity.h"
#include "Components/BaseComponent.h"

namespace AwesomeEngine
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

	public:
		Entity& CreateEntity();
		void DestroyEntity(Entity e);

		template <typename T> 
		void addComponent(Entity e, T component)
		{
			const auto componentId = BaseComponent::getNextId();
			const auto entityId = e.entityId;
			mEntities.push_back(e);

			//componentPool->set(entityId, component);
			//componentMasks[entityId].set(componentId);
		}

		//template <typename T>
		//T& EntityManager::getComponent(Entity e) const
		//{
		//	const auto componentId = BaseComponent::getNextId();
		//	const auto entityId = e.entityId;

		//	assert(hasComponent<T>(e));
		//	assert(componentId < componentPools.size());
		//	auto componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);

		//	assert(componentPool);
		//	assert(entityId < componentPool->getSize());
		//	return componentPool->get(entityId);
		//}

		//const ComponentMask& getComponentMask(Entity e) const;

	private:
		std::vector<Entity> mEntities;
	};

}