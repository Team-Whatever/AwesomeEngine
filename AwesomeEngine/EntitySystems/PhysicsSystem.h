#pragma once

#include "Mix/System.h"
#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"

namespace AwesomeEngine
{
	class PhysicsSystem : public Mix::System
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();

		virtual void Update(float delta);
		void UpdateEntity(Mix::Entity& entity, TransformComponent parentTransform, float delta);
	};

}