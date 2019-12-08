#pragma once
#include "Mix/System.h"

namespace AwesomeEngine
{
	class LuaScriptSystem : public Mix::System
	{
	public:
		LuaScriptSystem();
		~LuaScriptSystem();

		virtual void Update(float delta);
	};

}