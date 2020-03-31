#include "Character.h"
#include "Input/InputManager.h"
#include <DirectXMath.h>

using namespace AwesomeEngine;
using namespace DirectX;

namespace EscapeQ
{
	Character::Character()
	{
		
	}

	void Character::SetEntity(Mix::Entity& entity)
	{
		mEntity = entity;
	}

	void Character::Update(float delta)
	{
	}
}
