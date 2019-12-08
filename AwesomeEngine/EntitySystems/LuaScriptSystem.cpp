#include "LuaScriptSystem.h"
#include "Components/LuaScriptComponent.h"

namespace AwesomeEngine
{

	LuaScriptSystem::LuaScriptSystem()
	{
		requireComponent<LuaScriptComponent>();
	}

	LuaScriptSystem::~LuaScriptSystem()
	{
	}

	void LuaScriptSystem::Update(float delta)
	{
		for (auto& e : getEntities())
		{
			auto& script = e.getComponent<LuaScriptComponent>();
			script.Update(delta);
		}
	}

}