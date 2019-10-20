#pragma once


namespace AwesomeEngine
{
	struct HealthComponent
	{
		int health;
		int maxHealth;

		HealthComponent() {}
		// Constructor
		HealthComponent(int _health, int _maxHealth)
			: health(_health), maxHealth(_maxHealth) {}
	};
}
