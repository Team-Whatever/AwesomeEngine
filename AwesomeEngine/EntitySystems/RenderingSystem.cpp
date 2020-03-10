#include "RenderingSystem.h"

#include "Render\Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace AwesomeEngine
{

	RenderingSystem::RenderingSystem(Camera* camera)
	{
		requireComponent<CubeComponent>();
		mCamera = camera;
	}

	RenderingSystem::~RenderingSystem()
	{
	}


	void RenderingSystem::Update(float delta, std::shared_ptr<CommandList> commandList)
	{
		XMMATRIX viewMatrix = mCamera->get_ViewMatrix();
		XMMATRIX projectionMatrix = mCamera->get_ProjectionMatrix();
		for (auto& e : getEntities())
		{
			auto& renderItem = e.getComponent<CubeComponent>();
			renderItem.SetViewMatrix(viewMatrix);
			renderItem.SetProjectionMatrix(projectionMatrix);
			renderItem.OnRender(commandList);
		}
	}
}