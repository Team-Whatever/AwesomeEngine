#pragma once

#include "Mix/System.h"
#include "Components/PhysicsComponent.h"

namespace AwesomeEngine
{
	class PhysicsSystem : public Mix::System
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();

		virtual void Update(float delta);
	};

}