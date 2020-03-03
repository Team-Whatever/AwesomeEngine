#pragma once

#include "RenderComponent.h"
#include "Mesh.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct CubeComponent : public RenderComponent
	{
		CubeComponent(CommandList& commandList);

		virtual void Update(float delta);
		virtual void OnRender();

	private:

		std::unique_ptr<Mesh> m_CubeMesh;
		
	};
}
