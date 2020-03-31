#pragma once
#include "Mix/Entity.h"

namespace Mix
{
	class Entity;
}

namespace EscapeQ
{
	class Character
	{
	public:
		Character();

		void SetEntity(Mix::Entity& entity);

		virtual void Update(float delta);

	protected:
		Mix::Entity mEntity;
	};
}
