#include "LuaScriptComponent.h"
#include <iostream>
//#include <debugapi.h>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
using namespace luabridge;

void printMessage(const std::string& s)
{
	std::cout << s << std::endl;
}

void InitializeLuaScript(std::string filename)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	getGlobalNamespace(L).addFunction("printMessage", printMessage);

	
	luaL_dofile(L, filename.c_str());
	lua_pcall(L, 0, 0, 0);
	LuaRef s = getGlobal(L, "testString");
	printMessage(s.cast<std::string>());

	LuaRef init = getGlobal(L, "init");
	init();

	lua_close(L);
}

namespace AwesomeEngine
{
	LuaScriptComponent::LuaScriptComponent(std::string filename)
		: mLuaFileName( filename )
	{
		if (filename.size() > 0)
		{
			//InitializeLuaScript(filename);
			mLuaState = luaL_newstate();
			luaL_openlibs(mLuaState);
			getGlobalNamespace(mLuaState).addFunction("printMessage", printMessage);

			luaL_dofile(mLuaState, filename.c_str());
			lua_pcall(mLuaState, 0, 0, 0);
			LuaRef s = getGlobal(mLuaState, "testString");
			printMessage(s.cast<std::string>());

			//InitializeLuaScript();
		}
	}

	LuaScriptComponent::~LuaScriptComponent()
	{
		//if(mLuaState)
		//	lua_close(mLuaState);
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

				//char buffer[512];
				//sprintf_s(buffer, "script called: %d\n", called);
				//OutputDebugStringA(buffer);

				std::cout << "lua script update called : " << called << std::endl;
			}
		}
	}


}
