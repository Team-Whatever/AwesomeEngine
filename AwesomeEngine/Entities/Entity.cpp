#include "Entity.h"
#include "EntityManager.h"

namespace AwesomeEngine
{
	Entity::Entity(int id, EntityManager* manager)
		: entityId(id), pEntityManager(manager)
	{
	}


	Entity::~Entity()
	{
	}
}