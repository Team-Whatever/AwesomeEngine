#include "CylinderComponent.h"
#include "Render/Material.h"
#include "Render/Camera.h"
#include "Application.h"
#include "CommandQueue.h"

using namespace DirectX;
namespace AwesomeEngine
{
	CylinderComponent::CylinderComponent()
		: CylinderComponent(L"Assets/Textures/DefaultWhite.bmp")
	{
	}

	CylinderComponent::CylinderComponent(std::wstring textureName)
		: RenderComponent(textureName)
	{
	}

	void CylinderComponent::Initialize(std::shared_ptr<CommandList> commandList)
	{
		RenderComponent::Initialize(commandList);
		m_Mesh = Mesh::CreateCylinder(*commandList);
	}


	void CylinderComponent::Update(float delta)
	{
		//// Draw a cube
		//translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		//rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		//scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		//worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void CylinderComponent::OnRender(std::shared_ptr<CommandList> commandList)
	{
		if (!m_Initialized)
		{
			Initialize(commandList);
		}
		else
		{
			// Draw the earth sphere
			//XMMATRIX translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
			//XMMATRIX rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
			//XMMATRIX scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
			XMMATRIX worldMatrix = m_Scale * m_Rotation * m_Translation;

			Mat matrices;
			ComputeMatrices(worldMatrix, mViewMatrix, mProjectionMatrix, matrices);

			commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, matrices);
			commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, Material::White);
			commandList->SetShaderResourceView(RootParameters::Textures, 0, m_Texture, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

			m_Mesh->Render(*commandList);
		}
	}

}