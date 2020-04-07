#pragma once

#include "RenderComponent.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct CylinderComponent : public RenderComponent
	{
		CylinderComponent();
		CylinderComponent(std::wstring textureName);

		virtual void Initialize(std::shared_ptr<CommandList> commandList) override;
		virtual void Update(float delta) override;
		virtual void OnRender(std::shared_ptr<CommandList> commandList) override;
	};
}
