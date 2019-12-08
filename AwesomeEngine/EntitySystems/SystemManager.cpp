#include "SystemManager.h"

namespace AwesomeEngine
{
	void SystemManager::addToSystems(Entity e)
	{
		//const auto &entityComponentMask = mWorld.GetEntityManager().getComponentMask(e);

		//for (auto &it : mSystems) {
		//	auto &system = it.second;
		//	const auto &systemComponentMask = system->getComponentMask();
		//	auto interest = (entityComponentMask & systemComponentMask) == systemComponentMask;

		//	if (interest) {
		//		system->addEntity(e);
		//	}
		//}
	}

	void SystemManager::removeFromSystems(Entity e)
	{
		//for (auto &it : mSystems) {
		//	auto &system = it.second;
		//	system->removeEntity(e);
		//}
	}
}