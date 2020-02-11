#include "RenderingSystem.h"


namespace AwesomeEngine
{

	RenderingSystem::RenderingSystem()
	{
		requireComponent<RenderComponent>();
	}

	RenderingSystem::~RenderingSystem()
	{
	}


	void RenderingSystem::Update(float delta)
	{
		for (auto& e : getEntities())
		{
			auto& renderItem = e.getComponent<RenderComponent>();
			//renderItem.Draw(delta);
		}
	}
}