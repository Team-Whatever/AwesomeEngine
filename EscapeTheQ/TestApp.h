#pragma once
#include "AwesomeEngine.h"

class TestApp :public AwesomeEngine
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz) override;
	void Update(float dt) override;
	void Render(float dt) override;


};

TestApp::TestApp(HINSTANCE hInstance) : AwesomeEngine(hInstance)
{
}

TestApp::~TestApp()
{
}

bool TestApp::Init( unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	return AwesomeEngine::Init(diskRequiredInMB, memoryRequiredInMB, virtualMemoryRequriedInMB, cpuSpeedRequiredInMHz);
}

void TestApp::Update(float dt)
{
}

void TestApp::Render(float dt)
{
}
