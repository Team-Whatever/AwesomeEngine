#pragma once
#include "DirectXApp.h"
#include "Mix/World.h"

class EscapeTheQ : public DirectXApp
{
public:
	EscapeTheQ(const std::wstring& name, int width, int height, bool vSync = false);
	~EscapeTheQ();

	//bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz);
	virtual bool Initialize() override;
	void Update(float dt);
	void Render(float dt);

	Mix::World mWorld;
};
