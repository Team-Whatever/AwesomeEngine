#pragma once

#include "Mix/System.h"
#include <memory>

class Camera;
class CommandList;
namespace AwesomeEngine
{
	class PlaneRenderingSystem : public Mix::System
	{
	public:
		PlaneRenderingSystem();
		~PlaneRenderingSystem();

		virtual void Update(float delta, Camera* camera);
		virtual void Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera);
	};

}