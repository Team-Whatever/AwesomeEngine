#pragma once
#include "AbilitiesInterface.h"

namespace AwesomeGame
{
	class SpecialAbilityComponent : public IAbility
	{
	public:
		SpecialAbilityComponent();
		~SpecialAbilityComponent();

	public:
		virtual bool IsAbleToUseAbility() override;
		virtual void UseAbility() override;

	private:
		static const int MAX_MANA = 100;
		int mMana;
	};

}