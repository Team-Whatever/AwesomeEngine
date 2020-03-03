#include "EscapeTheQ.h"

#include "Input/InputEventSystem.h"
#include "Mix/Entity.h"

#include "Components/LuaScriptComponent.h"
#include "PythonScriptComponent.h"
#include <string>

using namespace AwesomeEngine;
EscapeTheQ::EscapeTheQ(const std::wstring& name, int width, int height, bool vSync)
	: AwesomeEngineApp( name, width, height, vSync )
{

}

EscapeTheQ::~EscapeTheQ()
{
}

bool EscapeTheQ::Initialize()
{
	bool isInit = AwesomeEngineApp::Initialize();
	if (isInit)
	{
		auto entity = CreateEntity();
		entity.addComponent(LuaScriptComponent("EscapeTheQ\\Scripts\\TestScript.lua"));
	}

	return isInit;
}

void EscapeTheQ::OnUpdate(UpdateEventArgs& e)
{
	AwesomeEngineApp::OnUpdate(e);
}
