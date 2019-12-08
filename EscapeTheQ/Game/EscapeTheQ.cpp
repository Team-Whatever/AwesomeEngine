#include "EscapeTheQ.h"
#include "Components/LuaScriptComponent.h"
#include "EntitySystems/LuaScriptSystem.h"
#include "Input/InputEventSystem.h"
#include "Mix/Entity.h"

using namespace AwesomeEngine;
EscapeTheQ::EscapeTheQ(HINSTANCE hInstance)
	: AwesomeEngineApp(hInstance)
{
}

EscapeTheQ::~EscapeTheQ()
{
}

bool EscapeTheQ::Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	bool isInit = AwesomeEngineApp::Init(diskRequiredInMB, memoryRequiredInMB, virtualMemoryRequriedInMB, cpuSpeedRequiredInMHz);
	if (isInit)
	{
		//mWorld.getSystemManager().addSystem<InputEventSystem>();
		mWorld.getSystemManager().addSystem<LuaScriptSystem>();

		// add lua component
		auto entity = mWorld.createEntity();
		entity.addComponent(LuaScriptComponent("Scripts/TestScript.lua"));
	}
	return isInit;
}

void EscapeTheQ::Update(float dt)
{
	mWorld.update();
	// TODO : polish entity component system
	//mWorld.getSystemManager().getSystem<InputEventSystem>().Update(dt);
	mWorld.getSystemManager().getSystem<LuaScriptSystem>().Update(dt);
}

void EscapeTheQ::Render(float dt)
{

}
