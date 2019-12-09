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
	void printMessage(const std::string& s) 
	{
		std::cout << s << std::endl;
	}

	LuaScriptComponent::LuaScriptComponent(std::string filename)
		: mLuaFileName( filename )
	{
		if (filename.size() > 0)
		{
			mLuaState = luaL_newstate();
			
			luaL_dofile(mLuaState, filename.c_str());
			luaL_openlibs(mLuaState);
			lua_pcall(mLuaState, 0, 0, 0);
			getGlobalNamespace(mLuaState).addFunction("printMessage", printMessage);

			LuaRef s = getGlobal(mLuaState, "testString");

			LuaRef update = getGlobal(mLuaState, "update");
			if (!update.isNil())
				return;
			//InitializeLuaScript();
		}
	}

	LuaScriptComponent::~LuaScriptComponent()
	{
		//if(mLuaState)
		//	lua_close(mLuaState);
	}

	void LuaScriptComponent::InitializeLuaScript()
	{
		if (mLuaState)
		{
			LuaRef init = getGlobal(mLuaState, "init");
			if (!init.isNil())
			{
				init();
				std::cout << "lua script component initialized : " << std::endl;
			}
		}
	}

	void LuaScriptComponent::Update(float delta)
	{
		if (mLuaState)
		{
			LuaRef update = getGlobal(mLuaState, "update");
			if (!update.isNil())
			{
				//lua_pushnumber(mLuaState, delta);
				//lua_call(mLuaState, 1, 1);
				//int called = lua_tointeger(mLuaState, -1);
				int called = update(delta);
				std::cout << "lua script update called : " << called << std::endl;
			}
		}
	}


}
