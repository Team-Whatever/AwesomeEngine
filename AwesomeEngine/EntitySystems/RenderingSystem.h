#pragma once

#include "Mix/System.h"
#include "Components/CubeComponent.h"
#include <memory>

class Camera;
namespace AwesomeEngine
{
	class RenderingSystem : public Mix::System
	{
	public:
		RenderingSystem(Camera* camera);
		~RenderingSystem();

		virtual void Update(float delta, std::shared_ptr<CommandList> commandList);

	private:
		Camera* mCamera;
	};

}