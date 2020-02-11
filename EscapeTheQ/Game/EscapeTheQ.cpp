#include "EscapeTheQ.h"
#include "Components/LuaScriptComponent.h"
#include "EntitySystems/PhysicsSystem.h"
#include "EntitySystems/LuaScriptSystem.h"
#include "Input/InputEventSystem.h"
#include "Mix/Entity.h"
#include "PythonScriptComponent.h"

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
		mWorld.getSystemManager().addSystem<PhysicsSystem>();
		mWorld.getSystemManager().addSystem<LuaScriptSystem>();

		// add lua component
		auto entity = mWorld.createEntity();
		entity.addComponent(LuaScriptComponent("Scripts/TestScript.lua"));
	}

	//PythonScriptComponent("")

	return isInit;
}

void EscapeTheQ::Update(float dt)
{
	mWorld.update();
	// TODO : polish entity component system
	mWorld.getSystemManager().getSystem<PhysicsSystem>().Update(dt);
	mWorld.getSystemManager().getSystem<LuaScriptSystem>().Update(dt);
}

void EscapeTheQ::Render(float dt)
{

}
