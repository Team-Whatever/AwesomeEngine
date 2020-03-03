#include "CubeComponent.h"
#include "Material.h"

using namespace DirectX;
namespace AwesomeEngine
{
	CubeComponent::CubeComponent(CommandList& commandList)
		: RenderComponent( commandList )
	{
		m_CubeMesh = Mesh::CreateCube(commandList);
	}

	void CubeComponent::Update(float delta)
	{
		//// Draw a cube
		//translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		//rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		//scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		//worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void CubeComponent::OnRender()
	{
		XMMATRIX translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		XMMATRIX rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		XMMATRIX scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		XMMATRIX worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
		XMMATRIX viewMatrix = m_Camera.get_ViewMatrix();
		XMMATRIX viewProjectionMatrix = viewMatrix * m_Camera.get_ProjectionMatrix();

		Mat matrices;
		ComputeMatrices(worldMatrix, viewMatrix, viewProjectionMatrix, matrices);

		m_CommandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, matrices);
		m_CommandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, Material::White);
		m_CommandList->SetShaderResourceView(RootParameters::Textures, 0, m_MonaLisaTexture, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		m_CubeMesh->Render(*m_CommandList);
	}

}