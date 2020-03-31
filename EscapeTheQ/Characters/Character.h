#pragma once
#include "Mix/Entity.h"

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
