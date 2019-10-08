#pragma once
#include "DXApp.h"

class TestApp :public DXApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz) override;
	void Update(float dt) override;
	void Render(float dt) override;


};

TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance)
{
}

TestApp::~TestApp()
{
}

bool TestApp::Init( unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	return DXApp::Init(diskRequiredInMB, memoryRequiredInMB, virtualMemoryRequriedInMB, cpuSpeedRequiredInMHz);
}

void TestApp::Update(float dt)
{
}

void TestApp::Render(float dt)
{
}
