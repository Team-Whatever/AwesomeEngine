#pragma once

#include "RenderComponent.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct ConeComponent : public RenderComponent
	{
		ConeComponent();
		ConeComponent(std::wstring textureName);

		virtual void Initialize(std::shared_ptr<CommandList> commandList) override;
		virtual void Update(float delta ) override;
		virtual void OnRender(std::shared_ptr<CommandList> commandList) override;
	};
}
