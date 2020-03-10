#pragma once

#include "RenderComponent.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct PlaneComponent : public RenderComponent
	{
		PlaneComponent();
		PlaneComponent(std::wstring textureName);

		virtual void Initialize(std::shared_ptr<CommandList> commandList) override;
		virtual void Update(float delta ) override;
		virtual void OnRender(std::shared_ptr<CommandList> commandList) override;
	};
}
