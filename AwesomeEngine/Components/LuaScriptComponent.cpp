#include "LuaScriptComponent.h"
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
using namespace luabridge;

namespace AwesomeEngine
{
	LuaScriptComponent::LuaScriptComponent(std::string filename)
	{
		mLuaState = luaL_newstate();
		luaL_dofile(mLuaState, filename.c_str());
		luaL_openlibs(mLuaState);
		lua_pcall(mLuaState, 0, 0, 0);

		LuaRef s = getGlobal(mLuaState, "testString");
		LuaRef n = getGlobal(mLuaState, "number");

		InitializeLuaScript();
	}

	LuaScriptComponent::~LuaScriptComponent()
	{
	}

	void LuaScriptComponent::InitializeLuaScript()
	{
		LuaRef init = getGlobal(mLuaState, "init");
		if (!init.isNil())
		{
			init();
			std::cout << "lua script component initialized : " << std::endl;
		}
	}

	void LuaScriptComponent::Update(float delta)
	{
		LuaRef update = getGlobal(mLuaState, "update");
		if (!update.isNil())
		{
			int called = update(delta);
			std::cout << "lua script update called : " << called << std::endl;
		}
	}


}
