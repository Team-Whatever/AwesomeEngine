#include "RenderComponent.h"

namespace AwesomeEngine
{
	void RenderComponent::Update(float delta)
	{
		//// Draw a cube
		//translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		//rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		//scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		//worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void RenderComponent::OnRender()
	{


		//ComputeMatrices(worldMatrix, viewMatrix, viewProjectionMatrix, matrices);

		//commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, matrices);
		//commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, Material::White);
		//commandList->SetShaderResourceView(RootParameters::Textures, 0, m_MonaLisaTexture, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		//m_CubeMesh->Draw(*commandList);
	}

	//void XM_CALLCONV RenderComponent::ComputeMatrices(FXMMATRIX model, CXMMATRIX view, CXMMATRIX viewProjection, Mat& mat)
	//{
	//	mat.ModelMatrix = model;
	//	mat.ModelViewMatrix = model * view;
	//	mat.InverseTransposeModelViewMatrix = XMMatrixTranspose(XMMatrixInverse(nullptr, mat.ModelViewMatrix));
	//	mat.ModelViewProjectionMatrix = model * viewProjection;
	//}
}