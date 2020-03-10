#include "SphereComponent.h"
#include "Render/Material.h"
#include "Application.h"
#include "CommandQueue.h"

using namespace DirectX;
namespace AwesomeEngine
{
	SphereComponent::SphereComponent()
		: SphereComponent(L"")
	{
	}

	SphereComponent::SphereComponent(std::wstring textureName)
		: RenderComponent(textureName)
	{
	}

	void SphereComponent::Initialize(std::shared_ptr<CommandList> commandList)
	{
		RenderComponent::Initialize(commandList);
		m_Mesh = Mesh::CreateSphere(*commandList);
	}

	void SphereComponent::Update(float delta)
	{
	}

	void SphereComponent::OnRender(std::shared_ptr<CommandList> commandList )
	{
		if (!m_Initialized)
		{
			Initialize(commandList);
		}
		else
		{
			//XMMATRIX translationMatrix = XMMatrixTranslation(-4.0f, 2.0f, -4.0f);
			//XMMATRIX rotationMatrix = XMMatrixIdentity();
			//XMMATRIX scaleMatrix = XMMatrixScaling(4.0f, 4.0f, 4.0f);
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