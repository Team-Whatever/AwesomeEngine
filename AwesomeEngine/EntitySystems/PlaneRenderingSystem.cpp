#include "PlaneRenderingSystem.h"

#include "Render/Camera.h"
#include "Components/PlaneComponent.h"
#include "Components/TransformComponent.h"

#include <DirectXMath.h>

using namespace DirectX;

namespace AwesomeEngine
{

	PlaneRenderingSystem::PlaneRenderingSystem()
	{
		requireComponent<PlaneComponent>();
		requireComponent<TransformComponent>();
	}

	PlaneRenderingSystem::~PlaneRenderingSystem()
	{
	}

	void PlaneRenderingSystem::Update(float delta, Camera* camera)
	{
		for (auto& e : getEntities())
		{
		}
	}

	void PlaneRenderingSystem::Render(float delta, std::shared_ptr<CommandList> commandList, Camera* camera)
	{
		if (!camera)
			return;

		XMMATRIX viewMatrix = camera->get_ViewMatrix();
		XMMATRIX projectionMatrix = viewMatrix * camera->get_ProjectionMatrix();
		for (auto& e : getEntities())
		{
			if (e.hasComponent<PlaneComponent>())
			{
				auto& renderItem = e.getComponent<PlaneComponent>();
				auto& transform = e.getComponent<TransformComponent>();

				renderItem.SetViewMatrix(viewMatrix);
				renderItem.SetProjectionMatrix(projectionMatrix);
				renderItem.SetTranslation(transform.position);
				renderItem.SetRotation(transform.rotation);
				renderItem.SetScale(transform.scale);
				renderItem.OnRender(commandList);
			}
		}
	}
}