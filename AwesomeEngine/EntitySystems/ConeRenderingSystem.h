#pragma once

#include "Mix/System.h"
#include <memory>

class Camera;
class CommandList;
namespace AwesomeEngine
{
	class ConeRenderingSystem : public Mix::System
	{
	public:
		ConeRenderingSystem();
		~ConeRenderingSystem();

		virtual void Update(float delta, Camera* camera);
		virtual void Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera);
	};

}