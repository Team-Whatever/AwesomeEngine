#include "TorusComponent.h"
#include "Render/Material.h"
#include "Application.h"
#include "CommandQueue.h"

using namespace DirectX;
namespace AwesomeEngine
{
	TorusComponent::TorusComponent()
		: TorusComponent(L"Assets/Textures/DefaultWhite.bmp")
	{
	}

	TorusComponent::TorusComponent(std::wstring textureName)
		: RenderComponent(textureName)
	{
	}

	void TorusComponent::Initialize(std::shared_ptr<CommandList> commandList)
	{
		RenderComponent::Initialize(commandList);
		m_Mesh = Mesh::CreateTorus(*commandList);
	}

	void TorusComponent::Update(float delta)
	{
	}

	void TorusComponent::OnRender(std::shared_ptr<CommandList> commandList )
	{
		if (!m_Initialized)
		{
			Initialize(commandList);
		}
		else
		{
			//XMMATRIX translationMatrix = XMMatrixTranslation(4.0f, 0.6f, -4.0f);
			//XMMATRIX rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
			//XMMATRIX scaleMatrix = XMMatrixScaling(4.0f, 4.0f, 4.0f);
			XMMATRIX worldMatrix = m_Scale * m_Rotation * m_Translation;

			Mat matrices;
			ComputeMatrices(worldMatrix, mViewMatrix, mProjectionMatrix, matrices);

			commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, matrices);
			commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, Material::Ruby);
			commandList->SetShaderResourceView(RootParameters::Textures, 0, m_Texture, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

			m_Mesh->Render(*commandList);
		}
	}

}