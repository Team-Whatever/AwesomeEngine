#include "EscapeTheQ.h"

#include "EntitySystems/PhysicsSystem.h"
#include "EntitySystems/LuaScriptSystem.h"
#include "EntitySystems/RenderingSystem.h"
#include "Input/InputEventSystem.h"
#include "Mix/Entity.h"

#include "Components/LuaScriptComponent.h"
#include "PythonScriptComponent.h"
#include <string>

using namespace AwesomeEngine;
EscapeTheQ::EscapeTheQ(const std::wstring& name, int width, int height, bool vSync)
	: DirectXApp( name, width, height, vSync )
{

}

EscapeTheQ::~EscapeTheQ()
{
}

bool EscapeTheQ::Initialize()
{
	bool isInit = DirectXApp::Initialize();
	if (isInit)
	{
		mWorld.getSystemManager().addSystem<PhysicsSystem>();
		mWorld.getSystemManager().addSystem<LuaScriptSystem>();
		mWorld.getSystemManager().addSystem<RenderingSystem>();

		auto entity = mWorld.createEntity();
		entity.addComponent(LuaScriptComponent("EscapeTheQ\\Scripts\\TestScript.lua"));
	}

	return isInit;
}

void EscapeTheQ::OnUpdate(UpdateEventArgs& e)
{
	DirectXApp::OnUpdate(e);
	mWorld.update();

	// TODO : polish entity component system
	mWorld.getSystemManager().getSystem<PhysicsSystem>().Update(e.ElapsedTime);
	mWorld.getSystemManager().getSystem<LuaScriptSystem>().Update(e.ElapsedTime);
	mWorld.getSystemManager().getSystem<RenderingSystem>().Update(e.ElapsedTime);
}

void EscapeTheQ::Render(float dt)
{

}
