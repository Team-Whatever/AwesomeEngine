#pragma once

#include "Mix/System.h"
#include "Components/TorusComponent.h"
#include "Components/TransformComponent.h"
#include <memory>

class Camera;
namespace AwesomeEngine
{
	class TorusRenderingSystem : public Mix::System
	{
	public:
		TorusRenderingSystem();
		~TorusRenderingSystem();

		virtual void Update(float delta, Camera* camera);
		virtual void Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera);
	};

}