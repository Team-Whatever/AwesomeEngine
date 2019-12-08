#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Entities/Entity.h"
#include "Entities/EntityManager.h"


namespace AwesomeEngine
{
	class SystemManager;

	class EntityWorld
	{
	public:
		EntityWorld();

		Entity& CreateEntity();
		EntityManager& GetEntityManager() const;
		SystemManager& GetSystemManager() const;
		//EventManager& GetEventManager() const;

		//void Update();
		//Entity CreateEntity();
		//void DestroyEntity(Entity e);

	private:
		// vector of entities that are awaiting creation
		std::vector<Entity> mCreatedEntities;

		// vector of entities that are awaiting destruction
		std::vector<Entity> mDestroyedEntities;

		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<SystemManager> mSystemManager = nullptr;
		//std::unique_ptr<EventManager> mEventManager = nullptr;
	};
}
