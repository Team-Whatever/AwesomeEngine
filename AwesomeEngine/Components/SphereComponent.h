#pragma once

#include "RenderComponent.h"
#include "Mesh.h"
#include "Texture.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct SphereComponent : public RenderComponent
	{
		SphereComponent();
		SphereComponent(std::wstring textureName);

		virtual void Initialize(std::shared_ptr<CommandList> commandList) override;
		virtual void Update(float delta ) override;
		virtual void OnRender(std::shared_ptr<CommandList> commandList ) override;
	};
}
#pragma once
