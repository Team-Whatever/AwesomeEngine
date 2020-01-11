#pragma once
#include <vector>

namespace AwesomeEngine
{
	class EntityManager;
	class Entity
	{
	public:
		Entity(int id, EntityManager* manager);
		Entity(int id, EntityManager* manager, Entity* Parent);
		~Entity();

		Entity& operator=(const Entity&) = default;
		/*
			Comparison operators.
		*/
		bool operator==(const Entity &e) const { return entityId == e.entityId; }
		bool operator!=(const Entity &e) const { return entityId != e.entityId; }
		bool operator<(const Entity &e) const { return entityId < e.entityId; }
	
		template <typename T>
		void addComponent(T component)
		{
			if(pEntityManager)
				pEntityManager->addComponent<T>(*this, component);
		}

		template <typename T>
		T& getComponent() const
		{
			return pEntityManager->getComponent<T>(*this);
		}

		void SetParent(Entity* newParent);
		void RemoveParent();
		void AddChild(Entity* newChild);
		void RemoveLastChild();
		void RemoveAllChildren();
		void DeleteEntity(Entity* newParentForChildren);

	public:
		unsigned int entityId;

	private:
		EntityManager* pEntityManager;
		friend class EntityManager;
		Entity* parent;
		std::vector<Entity*> children;
	};

}