#include "RenderingSystem.h"

#include "Render\Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace AwesomeEngine
{

	RenderingSystem::RenderingSystem(Camera* camera)
	{
		requireComponent<RenderComponent>();
		mCamera = camera;
	}

	RenderingSystem::~RenderingSystem()
	{
	}


	void RenderingSystem::Update(float delta)
	{
		XMMATRIX viewMatrix = mCamera->get_ViewMatrix();
		XMMATRIX projectionMatrix = mCamera->get_ProjectionMatrix();
		for (auto& e : getEntities())
		{
			auto& renderItem = e.getComponent<RenderComponent>();
			renderItem.SetViewMatrix(viewMatrix);
			renderItem.SetProjectionMatrix(projectionMatrix);
			renderItem.OnRender();
		}
	}
}