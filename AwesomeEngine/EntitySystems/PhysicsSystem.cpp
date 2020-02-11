#include "PhysicsSystem.h"

#include <DirectXMath.h>
namespace AwesomeEngine
{

	PhysicsSystem::PhysicsSystem()
	{
		requireComponent<PhysicsComponent>();
		requireComponent<TransformComponent>();
	}

	PhysicsSystem::~PhysicsSystem()
	{
	}

	void PhysicsSystem::Update(float delta)
	{
		for (auto& e : getEntities())
		{
			// only update root entity here
			if (e.GetParent() == nullptr)
			{
				TransformComponent transform;
				UpdateEntity(e, transform, delta);
			}
		}
	}

	void PhysicsSystem::UpdateEntity(Mix::Entity& entity, TransformComponent parentTransform, float delta)
	{
		auto& physicsBody = entity.getComponent<PhysicsComponent>();
		auto& transform = entity.getComponent<TransformComponent>();
		
		// TODO : update transfrom here
		physicsBody.Update(delta);

		for( auto child : entity.GetChildren() )
		{
			UpdateEntity(*child, transform, delta);
		}
	}

}