#pragma once

#include "BaseComponent.h"
#include "DirectXDefines.h"
#include "Mesh.h"
#include "Texture.h"

#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct RenderComponent : BaseComponent
	{
		RenderComponent();
		RenderComponent(std::wstring textureName);
		virtual void Initialize(std::shared_ptr<CommandList> commandList);
		virtual void Update(float delta ) = 0;
		virtual void OnRender( std::shared_ptr<CommandList> commandList) = 0;
		void SetViewMatrix(DirectX::XMMATRIX matrix);
		void SetProjectionMatrix(DirectX::XMMATRIX matrix);
		void SetTranslation(DirectX::XMVECTOR tranlation);
		void SetRotation(DirectX::XMVECTOR tranlation);
		void SetScale(DirectX::XMVECTOR tranlation);

	protected:
		void XM_CALLCONV ComputeMatrices(DirectX::FXMMATRIX model, DirectX::CXMMATRIX view, DirectX::CXMMATRIX viewProjection, Mat& mat);

	protected:
		DirectX::XMMATRIX m_Translation;
		DirectX::XMMATRIX m_Rotation;
		DirectX::XMMATRIX m_Scale;
		DirectX::XMMATRIX mViewMatrix;
		DirectX::XMMATRIX mProjectionMatrix;

		std::wstring m_TextureName;
		std::shared_ptr<Mesh> m_Mesh;
		Texture m_Texture;
		bool m_Initialized;
	};
}