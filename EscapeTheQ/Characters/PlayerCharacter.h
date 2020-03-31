#pragma once
#include "Character.h"

namespace EscapeQ
{
	class PlayerCharacter : public Character
	{
	public:
		PlayerCharacter();

	public:
		virtual void Update(float delta) override;
	};
}
