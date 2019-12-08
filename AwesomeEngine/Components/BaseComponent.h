#pragma once
#include <bitset>
#include <cassert>

namespace AwesomeEngine
{
	struct BaseComponent
	{
		static const int MAX_COMPONENTS = 64;
		static unsigned int nextId;
		static unsigned int getNextId()
		{ 
			static unsigned int id = nextId++;
			assert(id < MAX_COMPONENTS);
			return id; 
		}

		unsigned int id;
	};

	using ComponentMask = std::bitset<BaseComponent::MAX_COMPONENTS>;
}
