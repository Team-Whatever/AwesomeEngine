#pragma once
#include <string>

struct lua_State;
namespace AwesomeEngine
{
	struct LuaScriptComponent
	{
	public:
		LuaScriptComponent( std::string filename = "" );
		~LuaScriptComponent();

		void InitializeLuaScript();
		void Update(float delta);

	private:
		lua_State* mLuaState;

	};
}
