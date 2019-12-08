#pragma once
#include "AwesomeEngineApp.h"
#include "Mix/World.h"

class EscapeTheQ : public AwesomeEngineApp
{
public:
	EscapeTheQ(HINSTANCE hInstance);
	~EscapeTheQ();

	bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz) override;
	void Update(float dt) override;
	void Render(float dt) override;

	Mix::World mWorld;
};
