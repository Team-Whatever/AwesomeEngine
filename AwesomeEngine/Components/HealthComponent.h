#pragma once

#include "BaseComponent.h"

namespace AwesomeEngine
{
	struct HealthComponent : BaseComponent
	{
		int health;
		int maxHealth;

		HealthComponent() {}
		// Constructor
		HealthComponent(int _health, int _maxHealth)
			: health(_health), maxHealth(_maxHealth) {}
	};
}
