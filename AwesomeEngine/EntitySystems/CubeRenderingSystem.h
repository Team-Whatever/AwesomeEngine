#pragma once

#include "Mix/System.h"
#include "Components/CubeComponent.h"
#include "Components/TransformComponent.h"
#include <memory>

class Camera;
namespace AwesomeEngine
{
	class CubeRenderingSystem : public Mix::System
	{
	public:
		CubeRenderingSystem();
		~CubeRenderingSystem();

		virtual void Update(float delta, Camera* camera);
		virtual void Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera);
	};

}