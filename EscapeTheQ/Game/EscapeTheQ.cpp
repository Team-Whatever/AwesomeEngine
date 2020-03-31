#include "EscapeTheQ.h"

#include "Input/InputEventSystem.h"
#include "Input/InputManager.h"
#include "Mix/Entity.h"
#include "Characters/PlayerCharacter.h"

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
using namespace EscapeQ;

EscapeTheQ::EscapeTheQ(const std::wstring& name, int width, int height, bool vSync)
	: AwesomeEngineApp(name, width, height, vSync)
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

		auto torusEntity = CreateEntity();
		torusEntity.addComponent(TorusComponent(L"Assets/Textures/DefaultWhite.bmp"));
		torusEntity.SetLocation(XMVectorSet(4.0, 0.6f, -4.0f, 0.0f));
		torusEntity.SetScale(XMVectorSet(4.0f, 4.0f, 4.0f, 1.0f));

		mPlayer = std::make_shared<PlayerCharacter>();
		auto playerEntity = CreateEntity();
		playerEntity.addComponent(CubeComponent(L"Assets/Textures/Mona_Lisa.jpg"));
		playerEntity.SetLocation(XMVectorSet(4.0, 8.0f, 4.0f, 0.0f));
		playerEntity.SetScale(XMVectorSet(4.0f, 8.0f, 4.0f, 1.0f));
		playerEntity.AddChild(torusEntity);
		mPlayer->SetEntity(playerEntity);

		auto sphereEntity = CreateEntity();
		sphereEntity.addComponent(SphereComponent(L"Assets/Textures/earth.dds"));
		sphereEntity.SetLocation(XMVectorSet(-4.0, 2.0f, -4.0f, 0.0f));
		sphereEntity.SetScale(XMVectorSet(4.0f, 4.0f, 4.0f, 1.0f));

		auto sphereEntity2 = CreateEntity();
		sphereEntity2.addComponent(SphereComponent(L"Assets/Textures/Mona_Lisa.jpg"));
		sphereEntity2.SetLocation(XMVectorSet(-4.0, 6.0f, -4.0f, 0.0f));
		sphereEntity2.SetScale(XMVectorSet(2.0f, 2.0f, 2.0f, 1.0f));
		sphereEntity.AddChild(sphereEntity2);

		auto planeEntity = CreateEntity();
		planeEntity.addComponent(PlaneComponent(L"Assets/Textures/Directx9.png"));
		planeEntity.SetLocation(XMVectorSet(0.0, 0.0f, 0.0f, 0.0f));
		planeEntity.SetScale(XMVectorSet(20.0f, 1.0f, 20.0f, 1.0f));

		auto coneEntity = CreateEntity();
		coneEntity.addComponent(ConeComponent(L"Assets/Textures/DefaultWhite.bmp"));
		coneEntity.SetLocation(XMVectorSet(0.0, 10.0f, 0.0f, 0.0f));

	}

	return isInit;
}

void EscapeTheQ::OnUpdate(UpdateEventArgs& e)
{
	AwesomeEngineApp::OnUpdate(e);

	mPlayer->Update(e.ElapsedTime);

}
