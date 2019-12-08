#pragma once

#include <vector>
#include "Entities/Entity.h"
#include "EntityWorld.h"
#include "Components/BaseComponent.h"

namespace AwesomeEngine
{

	// The system processes entities that it's interested in each frame. Derive from this one!
	class EntitySystem
	{
	public:
		virtual ~EntitySystem() {}

		// what component types the system requires of entities (we can use this method in the constructor for example)
		template <typename T>
		void requireComponent();

		// returns a list of entities that the system should process each frame
		std::vector<Entity> getEntities() { return entities; }

		// adds an entity of interest
		void addEntity(Entity e);

		// if the entity is not alive anymore (during processing), the entity should be removed
		void removeEntity(Entity e);

		const ComponentMask& getComponentMask() const { return componentMask; }

	protected:
		EntityWorld& getWorld() const;

	private:
		// which components an entity must have in order for the system to process the entity
		ComponentMask componentMask;

		// vector of all entities that the system is interested in
		std::vector<Entity> entities;

		EntityWorld *world = nullptr;
		friend class SystemManager;
	};

	template <typename T>
	void EntitySystem::requireComponent()
	{
		const auto componentId = BaseComponent::getNextId();
		componentMask.set(componentId);
	}
}
