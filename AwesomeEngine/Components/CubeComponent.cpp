#include "CubeComponent.h"
#include "Render/Material.h"
#include "Application.h"
#include "CommandQueue.h"

using namespace DirectX;
namespace AwesomeEngine
{
	CubeComponent::CubeComponent()
		: CubeComponent( L"" )
	{
	}

	CubeComponent::CubeComponent(std::wstring textureName)
		: RenderComponent()
	{
		auto commandQueue = Application::Get().GetCommandQueue(D3D12_COMMAND_LIST_TYPE_COPY);
		auto commandList = commandQueue->GetCommandList();

		m_CubeMesh = Mesh::CreateCube(*commandList);
		if (textureName.size() > 0)
		{
			Texture cubeTexture;
			commandList->LoadTextureFromFile(cubeTexture, textureName.c_str());
			m_CubeTexture = std::make_shared<Texture>(cubeTexture);
		}
	}

	void CubeComponent::Update(float delta)
	{
		//// Draw a cube
		//translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		//rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		//scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		//worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void CubeComponent::OnRender(std::shared_ptr<CommandList> commandList)
	{
		XMMATRIX translationMatrix = XMMatrixTranslation(4.0f, 4.0f, 4.0f);
		XMMATRIX rotationMatrix = XMMatrixRotationY(XMConvertToRadians(45.0f));
		XMMATRIX scaleMatrix = XMMatrixScaling(4.0f, 8.0f, 4.0f);
		XMMATRIX worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
		XMMATRIX viewProjectionMatrix = mViewMatrix * mProjectionMatrix;

		Mat matrices;
		ComputeMatrices(worldMatrix, mViewMatrix, viewProjectionMatrix, matrices);

		commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, matrices);
		commandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, Material::White);
		commandList->SetShaderResourceView(RootParameters::Textures, 0, *m_CubeTexture.get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		m_CubeMesh->Render(*commandList);
	}

}