#pragma once

#include "EntitySystem.h"
#include "EntityWorld.h"

namespace AwesomeEngine
{
	class SystemManager
	{
	public:
		SystemManager(EntityWorld &world) 
			: mWorld(world) {}

		template <typename T>
		void addSystem();

		template <typename T, typename ... Args>
		void addSystem(Args && ... args);

		template <typename T>
		void removeSystem();

		template <typename T>
		T& getSystem();

		template <typename T>
		bool hasSystem() const;

		// adds an entity to each system that is interested of the entity
		void addToSystems(Entity e);

		// removes an entity from interested systems' entity lists
		void removeFromSystems(Entity e);

	private:
		std::unordered_map<std::type_index, std::shared_ptr<EntitySystem>> mSystems;

		EntityWorld& mWorld;
	};


	template <typename T>
	void SystemManager::addSystem()
	{
		if (hasSystem<T>()) {
			return;
		}

		std::shared_ptr<T> system(new T);
		system->world = &mWorld;
		mSystems.insert(std::make_pair(std::type_index(typeid(T)), system));
	}

	template <typename T, typename ... Args>
	void SystemManager::addSystem(Args && ... args)
	{
		if (hasSystem<T>()) {
			return;
		}

		std::shared_ptr<T> system(new T(std::forward<Args>(args) ...));
		system->world = &mWorld;
		mSystems.insert(std::make_pair(std::type_index(typeid(T)), system));
	}

	template <typename T>
	void SystemManager::removeSystem()
	{
		if (!hasSystem<T>()) {
			return;
		}

		auto it = mSystems.find(std::type_index(typeid(T)));
		mSystems.erase(it);
	}

	template <typename T>
	T& SystemManager::getSystem()
	{
		if (!hasSystem<T>()) {
			throw std::runtime_error(std::string("Failed to get system: ") + typeid(T).name());
		}

		auto it = mSystems.find(std::type_index(typeid(T)));
		return *(std::static_pointer_cast<T>(it->second));
	}

	template <typename T>
	bool SystemManager::hasSystem() const
	{
		return mSystems.find(std::type_index(typeid(T))) != mSystems.end();
	}
}