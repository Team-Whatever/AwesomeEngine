#pragma once

#include <vector>
#include "Entities/Entity.h"

namespace AwesomeEngine
{
	class EntitySystem
	{
	public:
		EntitySystem();

	private:
		std::vector<Entity> entities;
	};
}
