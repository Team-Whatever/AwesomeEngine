#pragma once
#define WIN32_LEAN_AND_MEAN //not cryptography and networking...
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <Windows.h>
#include <string>
#include "atltypes.h"

class AwesomeEngine
{
public:
	AwesomeEngine(HINSTANCE hInstance); //instance of the application (not window!)
	virtual ~AwesomeEngine();

	//Main Application Loop
	int Run();

	//Framework Methods
	virtual bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz);
	virtual void Update(float dt) = 0;
	virtual void Render(float dt) = 0; // dt for animation
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool IsOnlyInstance(LPCTSTR gameTitle);

	bool CheckStorage(const DWORDLONG diskSpaceNeededInMB);

	DWORD ReadCPUSpeed();

protected:

	//WIN32 Attributes
	HWND  m_hAppWnd;
	HINSTANCE m_hAppInstance;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	std::string m_AppTitle;
	DWORD m_WndStyle;

protected:
	bool InitWindow();


};