#pragma once


namespace AwesomeGame
{
	class IAbility
	{
	public:
		// check if the component can use the ability 
		virtual bool IsAbleToUseAbility() = 0;

		// execute the ability
		virtual void UseAbility() = 0;

	protected:
		int abilityCost;

	};
}