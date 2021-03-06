#pragma once
#define WIN32_LEAN_AND_MEAN //not cryptography and networking...
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <Windows.h>
#include <string>

#include "DirectXApp.h"
#include "Events/IEventData.h"
#include "Mix/Entity.h"
#include "Managers/SceneLoader.h"

namespace Gdiplus
{
	class Image;
}

class AwesomeEngineApp : public DirectXApp
{
public:
	AwesomeEngineApp(const std::wstring& name, int width, int height, bool vSync = false); //instance of the application (not window!)
	virtual ~AwesomeEngineApp();

	virtual bool Initialize();
	virtual void OnUpdate(UpdateEventArgs& e);
	Mix::Entity CreateEntity();
	void LoadScene( std::string sceneName );

public:
	int Run();

	//Framework Methods
	virtual bool CheckRequirements(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz);
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool IsOnlyInstance(LPCTSTR gameTitle);
	bool CheckStorage(const DWORDLONG diskSpaceNeededInMB);
	DWORD ReadCPUSpeed();

	// Event Listener Test
	void EventMouseClicked(const EventParam param);
	void EventMouseMoved(const EventParam param);
	void EventKeyPressed(const EventParam param);

protected:
	bool InitWindow();

private:
	void InitLuaScript();

protected:

	//WIN32 Attributes
	HWND  m_hAppWnd;
	HINSTANCE m_hAppInstance;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	std::string m_AppTitle;
	DWORD m_WndStyle;
	Gdiplus::Image* m_LogoImage;
	AwesomeEngine::SceneLoader m_SceneLoader;

};