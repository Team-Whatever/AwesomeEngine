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

	RenderComponent::RenderComponent(std::wstring textureName)
		: m_TextureName( textureName ), m_Initialized( false )
	{
	}

	void RenderComponent::Initialize(std::shared_ptr<CommandList> commandList)
	{
		if (m_TextureName.size() > 0)
		{
			commandList->LoadTextureFromFile(m_Texture, m_TextureName.c_str());
		}
		m_Initialized = true;
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