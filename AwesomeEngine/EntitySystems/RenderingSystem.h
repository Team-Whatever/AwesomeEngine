#pragma once

#include "Mix/System.h"
#include "Components/RenderComponent.h"

namespace AwesomeEngine
{
	class RenderingSystem : public Mix::System
	{
	public:
		RenderingSystem();
		~RenderingSystem();

		virtual void Update(float delta);
	};

}