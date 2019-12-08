#include "EntityWorld.h"
//#include "Entities/EntityManager.h"
#include "EntitySystems/SystemManager.h"


namespace AwesomeEngine
{
	EntityWorld::EntityWorld()
	{
		mEntityManager = std::make_unique<EntityManager>();
		mSystemManager = std::make_unique<SystemManager>(*this);
		//mEventManager = std::make_unique<EventManager>(*this);
	}

	Entity & EntityWorld::CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}


	EntityManager& EntityWorld::GetEntityManager() const
	{
		assert(mEntityManager != nullptr);
		return *mEntityManager;
	}

	SystemManager& EntityWorld::GetSystemManager() const
	{
		assert(mSystemManager != nullptr);
		return *mSystemManager;
	}

	//void World::update()
	//{
	//	for (auto e : createdEntities) {
	//		getSystemManager().addToSystems(e);
	//	}
	//	createdEntities.clear();

	//	for (auto e : destroyedEntities) {
	//		getSystemManager().removeFromSystems(e);
	//		getEntityManager().destroyEntity(e);
	//	}
	//	destroyedEntities.clear();

	//	getEventManager().destroyEvents();
	//}

	//Entity World::createEntity()
	//{
	//	auto e = getEntityManager().createEntity();
	//	createdEntities.push_back(e);
	//	return e;
	//}

	//void World::destroyEntity(Entity e)
	//{
	//	destroyedEntities.push_back(e);
	//}

	//Entity World::getEntity(std::string tag) const
	//{
	//	return getEntityManager().getEntityByTag(tag);
	//}
}
