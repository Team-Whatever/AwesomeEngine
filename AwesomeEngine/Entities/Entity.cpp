#include "Entity.h"
#include "EntityManager.h"

namespace AwesomeEngine
{
	Entity::Entity(int id, EntityManager* manager)
		: entityId(id), pEntityManager(manager), parent(nullptr)
	{

	}

	Entity::Entity(int id, EntityManager* manager, Entity* Parent)
		: entityId(id), pEntityManager(manager), parent(Parent)
	{
	}


	Entity::~Entity()
	{
	}

	void Entity::SetParent(Entity* newParent)
	{
		parent = newParent;
	}

	void Entity::RemoveParent()
	{
		parent = nullptr;
	}

	void Entity::AddChild(Entity* newChild)
	{
		children.push_back(newChild);
		newChild->SetParent(this);
	}

	void Entity::RemoveLastChild()
	{
		children.pop_back();
	}

	void Entity::RemoveAllChildren()
	{
		Entity* childToClear;
		for (auto it = children.begin(); it != children.end(); it++)
		{
			childToClear = *it;
			childToClear->RemoveParent();
		}
		children.clear();
	}

	void Entity::DeleteEntity(Entity* newParentForChildren)
	{
		Entity* childToReParent;
		for (auto it = children.begin(); it != children.end(); it++)
		{			
			childToReParent = *it;
			childToReParent->SetParent(newParentForChildren);
		}
		delete this;
	}
}