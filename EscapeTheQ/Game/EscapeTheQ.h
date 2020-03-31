#pragma once
#include "AwesomeEngineApp.h"
#include "Characters/PlayerCharacter.h"

class EscapeTheQ : public AwesomeEngineApp
{
public:
	EscapeTheQ(const std::wstring& name, int width, int height, bool vSync = false);
	~EscapeTheQ();

	//bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz);
	virtual bool Initialize() override;
	virtual void OnUpdate(UpdateEventArgs& e) override;

private:
	std::unique_ptr<EscapeQ::PlayerCharacter> mPlayer;
};
