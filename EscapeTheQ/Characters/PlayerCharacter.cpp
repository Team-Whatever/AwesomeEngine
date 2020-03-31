#include "PlayerCharacter.h"
#include "Input/InputManager.h"
#include "Components/TransformComponent.h"
#include "Mix/Entity.h"
#include <DirectXMath.h>

using namespace AwesomeEngine;
using namespace DirectX;
namespace EscapeQ
{
	PlayerCharacter::PlayerCharacter()
	{

	}

	void PlayerCharacter::Update(float delta)
	{
		float speedMultipler = 4.0f;
		float forward = 0.0f;
		if (InputManager::GetInstance().IsKeyPressed(KeyCode::W))
		{
			forward += 1.0f;
		}
		else if (InputManager::GetInstance().IsKeyPressed(KeyCode::S))
		{
			forward -= 1.0f;
		}

		float right = 0.0f;
		if (InputManager::GetInstance().IsKeyPressed(KeyCode::A))
		{
			right -= 1.0f;
		}
		else if (InputManager::GetInstance().IsKeyPressed(KeyCode::D))
		{
			right += 1.0f;
		}

		XMVECTOR translate = XMVectorSet(right, 0.0f, forward, 1.0f) * speedMultipler * delta;
		//player.Translate(translate, Space::Local);
		//auto& transform = mEntity.getComponent<TransformComponent>();
		mEntity.Translate(translate);
	}
}
