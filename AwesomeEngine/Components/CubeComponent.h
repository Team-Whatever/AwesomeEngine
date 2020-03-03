#pragma once

#include "RenderComponent.h"
#include "Mesh.h"
#include "Texture.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct CubeComponent : public RenderComponent
	{
		CubeComponent();
		CubeComponent(std::wstring textureName);

		virtual void Update(float delta);
		virtual void OnRender();

	private:

		std::shared_ptr<Mesh> m_CubeMesh;
		Texture m_CubeTexture;
		
	};
}
