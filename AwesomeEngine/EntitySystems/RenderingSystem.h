#pragma once

#include "Mix/System.h"
#include "Components/RenderComponent.h"
#include <memory>

class Camera;
namespace AwesomeEngine
{
	class RenderingSystem : public Mix::System
	{
	public:
		RenderingSystem(Camera* camera);
		~RenderingSystem();

		virtual void Update(float delta);

	private:
		Camera* mCamera;
	};

}