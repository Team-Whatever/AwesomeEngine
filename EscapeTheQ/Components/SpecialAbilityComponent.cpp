#include "SpecialAbilityComponent.h"
#include <iostream>

namespace EscapeQ
{
	SpecialAbilityComponent::SpecialAbilityComponent()
		: mMana(MAX_MANA)
	{
		abilityCost = 30;
	}


	SpecialAbilityComponent::~SpecialAbilityComponent()
	{
	}


	bool SpecialAbilityComponent::IsAbleToUseAbility()
	{
		return mMana >= abilityCost;
	}

	void SpecialAbilityComponent::UseAbility()
	{
		mMana -= abilityCost;
		// do soemthing special here.
		std::cout << "Use Special Ability : " << std::endl;
	}
}