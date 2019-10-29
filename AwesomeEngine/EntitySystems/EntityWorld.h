#pragma once
#include <vector>
#include <memory>

#include "Entities/Entity.h"


class EntityManager;

namespace AwesomeEngine
{
	class EntityWorld
	{
	public:
		EntityWorld();

		Entity& CreateEntity();

	private:
		std::vector<Entity> entities;
		std::vector<Entity> destroying;

		std::unique_ptr<EntityManager> entityManager;

	};
}
