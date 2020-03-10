#include "SphereRenderingSystem.h"

#include "Render\Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace AwesomeEngine
{

	SphereRenderingSystem::SphereRenderingSystem()
	{
		requireComponent<SphereComponent>();
	}

	SphereRenderingSystem::~SphereRenderingSystem()
	{
	}

	void SphereRenderingSystem::Update(float delta, Camera* camera)
	{
		for (auto& e : getEntities())
		{
		}
	}

	void SphereRenderingSystem::Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera)
	{
		if (!camera)
			return;

		XMMATRIX viewMatrix = camera->get_ViewMatrix();
		XMMATRIX projectionMatrix = viewMatrix * camera->get_ProjectionMatrix();
		for (auto& e : getEntities())
		{
			if (e.hasComponent<SphereComponent>())
			{
				auto& renderItem = e.getComponent<SphereComponent>();
				renderItem.SetViewMatrix(viewMatrix);
				renderItem.SetProjectionMatrix(projectionMatrix);
				renderItem.OnRender(commandList);
			}
		}
	}
}