#include "EntityWorld.h"
//#include "Entities/EntityManager.h"


namespace AwesomeEngine
{
	EntityWorld::EntityWorld()
	{
		entityManager = std::make_unique<EntityManager>();
	}

	Entity & EntityWorld::CreateEntity()
	{
		Entity e = entityManager->CreateEntity();
		entities.push_back(e);
		return e;


	}
}
