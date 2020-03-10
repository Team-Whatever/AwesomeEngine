#include "EscapeTheQ.h"

#include "Input/InputEventSystem.h"
#include "Mix/Entity.h"

#include "Components/LuaScriptComponent.h"
#include "Components/CubeComponent.h"
#include "Components/TorusComponent.h"
#include "Components/SphereComponent.h"
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
		entity.addComponent(LuaScriptComponent("EscapeTheQ/Scripts/TestScript.lua"));

		auto cubeEntity = CreateEntity();
		cubeEntity.addComponent(CubeComponent(L"Assets/Textures/Mona_Lisa.jpg"));

		auto torusEntity = CreateEntity();
		torusEntity.addComponent(TorusComponent(L"Assets/Textures/DefaultWhite.bmp"));

		auto sphereEntity = CreateEntity();
		sphereEntity.addComponent(SphereComponent(L"Assets/Textures/earth.dds"));

	}

	return isInit;
}

void EscapeTheQ::OnUpdate(UpdateEventArgs& e)
{
	AwesomeEngineApp::OnUpdate(e);
}
