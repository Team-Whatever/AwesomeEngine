#pragma once
#define WIN32_LEAN_AND_MEAN //not cryptography and networking...
#include <Windows.h>
#include <string>
#include "atltypes.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance); //instance of the application (not window!)
	virtual ~DXApp();

	//Main Application Loop
	int Run();

	//Framework Methods
	virtual bool Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz);
	virtual void Update(float dt) = 0;
	virtual void Render(float dt) = 0; // dt for animation
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool IsOnlyInstance(LPCTSTR gameTitle);

	bool CheckStorage(const DWORDLONG diskSpaceNeededInMB);

	//keyboard handler
	virtual bool VOnKeyDown(unsigned int const keycode) = 0;
	virtual bool VOnKeyUp(unsigned int const keycode) = 0; 

	//mouse handler
	virtual bool VOnPointerMove(const CPoint &mousePos) = 0;
	virtual bool VOnPointerButtonDown(const CPoint &mousePos, const std::string &buttonName) = 0;
	virtual bool VOnPointerButtonUp(const CPoint &mousePos, const std::string &buttonName) = 0;
	virtual bool VGetPointerRadius()=0;

	//joystick
	virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
	virtual bool VOnButtonUp(const std::string &buttonName) = 0;
	virtual bool VOnJoystick(float const x, float const y) = 0;

	//gamepad
	virtual bool VOnTrigger(const std::string &triggerName, float const pressure) = 0;
	virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
	virtual bool VOnButtonUp(const std::string &buttonName) = 0; 
	virtual bool VOnDirectionalPad(const std::string &direction) = 0;
	virtual bool VOnThumbstick(const std::string &stickName, float const x, float const y) = 0; 


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