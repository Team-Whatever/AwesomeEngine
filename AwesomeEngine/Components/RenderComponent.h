#pragma once

#include "BaseComponent.h"
#include "DirectXDefines.h"
#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct RenderComponent : BaseComponent
	{
		RenderComponent();
		virtual void Update(float delta);
		virtual void OnRender();
		void SetViewMatrix(DirectX::XMMATRIX matrix);
		void SetProjectionMatrix(DirectX::XMMATRIX matrix);

	protected:
		void XM_CALLCONV ComputeMatrices(DirectX::FXMMATRIX model, DirectX::CXMMATRIX view, DirectX::CXMMATRIX viewProjection, Mat& mat);

	protected:
		DirectX::XMMATRIX mViewMatrix;
		DirectX::XMMATRIX mProjectionMatrix;
	};
}