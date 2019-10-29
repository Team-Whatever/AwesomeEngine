#pragma once

#include "Entity.h"

namespace AwesomeEngine
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

	public:

		Entity CreateEntity();
		void DestroyEntity(Entity e);

		
	};

}