#include "RenderComponent.h"
#include "Application.h"
#include "CommandQueue.h"
#include <DirectXMath.h>

using namespace DirectX;
namespace AwesomeEngine
{
	RenderComponent::RenderComponent()
	{
	}

	void RenderComponent::Update(float delta)
	{
		//// Draw a cube
		//translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		//rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		//scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		//worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void RenderComponent::OnRender( std::shared_ptr<CommandList> commandList )
	{
		//ComputeMatrices(worldMatrix, viewMatrix, viewProjectionMatrix, matrices);

		//commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, matrices);
		//commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, Material::White);
		//commandList->SetShaderResourceView(RootParameters::Textures, 0, m_MonaLisaTexture, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		//m_CubeMesh->Draw(*commandList);
	}

	void RenderComponent::SetViewMatrix(DirectX::XMMATRIX matrix)
	{
		mViewMatrix = matrix;
	}

	void RenderComponent::SetProjectionMatrix(DirectX::XMMATRIX matrix)
	{
		mProjectionMatrix = matrix;
	}

	void XM_CALLCONV RenderComponent::ComputeMatrices(FXMMATRIX model, CXMMATRIX view, CXMMATRIX viewProjection, Mat& mat)
	{
		mat.ModelMatrix = model;
		mat.ModelViewMatrix = model * view;
		mat.InverseTransposeModelViewMatrix = XMMatrixTranspose(XMMatrixInverse(nullptr, mat.ModelViewMatrix));
		mat.ModelViewProjectionMatrix = model * viewProjection;
	}
}