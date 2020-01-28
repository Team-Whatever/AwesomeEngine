#include "PhysicsSystem.h"

namespace AwesomeEngine
{

	PhysicsSystem::PhysicsSystem()
	{
		requireComponent<PhysicsComponent>();
	}

	PhysicsSystem::~PhysicsSystem()
	{
	}

	void PhysicsSystem::Update(float delta)
	{
		for (auto& e : getEntities())
		{
			
			auto& physicsBody = e.getComponent<PhysicsComponent>();
			physicsBody.Update(delta);
		}

	}

}