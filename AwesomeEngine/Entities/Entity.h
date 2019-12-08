#pragma once

namespace AwesomeEngine
{
	class EntityManager;
	class Entity
	{
	public:
		Entity(int id, EntityManager* manager);
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

	public:
		unsigned int entityId;

	private:
		EntityManager* pEntityManager;
		friend class EntityManager;
	};

}