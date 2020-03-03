#pragma once

#include "BaseComponent.h"
#include "DirectXDefines.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct RenderComponent : BaseComponent
	{
		RenderComponent(CommandList& commandList);
		virtual void Update(float delta);
		virtual void OnRender();

	protected:
		void XM_CALLCONV ComputeMatrices(FXMMATRIX model, CXMMATRIX view, CXMMATRIX viewProjection, Mat& mat);

	protected:
		CommandList* m_CommandList;
	};
}