#pragma once
#include "AbilitiesInterface.h"

#include "Components/BaseComponent.h"

namespace Escape
{

	class SpecialAbilityComponent : public AwesomeEngine::BaseComponent, IAbility
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