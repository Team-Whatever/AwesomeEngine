#include "EscapeTheQ.h"

#include "Input/InputEventSystem.h"
#include "Mix/Entity.h"

#include "Components/TransformComponent.h"
#include "Components/LuaScriptComponent.h"
#include "Components/CubeComponent.h"
#include "Components/TorusComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PlaneComponent.h"
#include "Components/ConeComponent.h"
#include "PythonScriptComponent.h"
#include <string>

using namespace AwesomeEngine;
using namespace DirectX;
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
		cubeEntity.addComponent(TransformComponent(XMVectorSet(4.0, 8.0f, 4.0f, 0.0f), XMVectorSet( 4.0f, 8.0f, 4.0f, 1.0f ) ));

		auto torusEntity = CreateEntity();
		torusEntity.addComponent(TorusComponent(L"Assets/Textures/DefaultWhite.bmp"));
		torusEntity.addComponent(TransformComponent(XMVectorSet(4.0, 0.6f, -4.0f, 0.0f), XMVectorSet(4.0f, 4.0f, 4.0f, 1.0f)));

		auto sphereEntity = CreateEntity();
		sphereEntity.addComponent(SphereComponent(L"Assets/Textures/earth.dds"));
		sphereEntity.addComponent(TransformComponent(XMVectorSet(-4.0, 2.0f, -4.0f, 0.0f), XMVectorSet(4.0f, 4.0f, 4.0f, 1.0f)));

		auto sphereEntity2 = CreateEntity();
		sphereEntity2.addComponent(SphereComponent(L"Assets/Textures/Mona_Lisa.jpg"));
		sphereEntity2.addComponent(TransformComponent(XMVectorSet(-4.0, 6.0f, -4.0f, 0.0f), XMVectorSet(2.0f, 2.0f, 2.0f, 1.0f)));

		auto planeEntity = CreateEntity();
		planeEntity.addComponent(PlaneComponent(L"Assets/Textures/Directx9.png"));
		planeEntity.addComponent(TransformComponent(XMVectorSet(0.0, 0.0f, 0.0f, 0.0f), XMVectorSet(20.0f, 1.0f, 20.0f, 1.0f)));

		auto coneEntity = CreateEntity();
		coneEntity.addComponent(ConeComponent(L"Assets/Textures/DefaultWhite.bmp"));
		coneEntity.addComponent(TransformComponent(XMVectorSet(0.0, 10.0f, 0.0f, 0.0f)));

	}

	return isInit;
}

void EscapeTheQ::OnUpdate(UpdateEventArgs& e)
{
	AwesomeEngineApp::OnUpdate(e);
}
