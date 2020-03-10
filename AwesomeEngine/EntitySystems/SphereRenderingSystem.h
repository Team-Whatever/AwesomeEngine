#pragma once

#include "Mix/System.h"
#include "Components/TransformComponent.h"
#include "Components/SphereComponent.h"
#include <memory>

class Camera;
namespace AwesomeEngine
{
	class SphereRenderingSystem : public Mix::System
	{
	public:
		SphereRenderingSystem();
		~SphereRenderingSystem();

		virtual void Update(float delta, Camera* camera);
		virtual void Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera);
	};

}