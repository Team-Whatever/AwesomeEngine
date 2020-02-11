#pragma once

#include "BaseComponent.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct RenderComponent : BaseComponent
	{
		RenderComponent()
		{
		}

		void Update(float delta);
		void OnRender();

	private:
		//void XM_CALLCONV ComputeMatrices(FXMMATRIX model, CXMMATRIX view, CXMMATRIX viewProjection, Mat& mat);
	};
}