#pragma once
#include "AwesomeEngineApp.h"

class GameApp :public AwesomeEngineApp
{
public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz) override;
	void Update(float dt) override;
	void Render(float dt) override;


};

GameApp::GameApp(HINSTANCE hInstance) : AwesomeEngineApp(hInstance)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init( unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	return AwesomeEngineApp::Init(diskRequiredInMB, memoryRequiredInMB, virtualMemoryRequriedInMB, cpuSpeedRequiredInMHz);
}

void GameApp::Update(float dt)
{
}

void GameApp::Render(float dt)
{
}
