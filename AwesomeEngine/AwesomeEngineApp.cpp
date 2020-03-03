
#include "AwesomeEngineApp.h"
#include <iostream>
#include <sstream>
#include <direct.h>
#include <string.h>
#include <windowsx.h>
#include <tchar.h>
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplusbase.h>
#include <gdiplusgraphics.h>
#include <thread>
#include <chrono>
#include <mutex>

#include "Events/EventManager.h"
#include "EntitySystems/PhysicsSystem.h"
#include "EntitySystems/LuaScriptSystem.h"
#include "EntitySystems/RenderingSystem.h"

using namespace Gdiplus;
#pragma comment (lib, "gdiplus.lib")


extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
using namespace luabridge;

namespace {
	//used to forward messages to user defined proc function
	AwesomeEngineApp* g_App = nullptr;
}

using namespace AwesomeEngine;

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken = NULL;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//step4:Window procedures are functions we implement which contain code that is to be executed in response to specific messages.
	if (g_App)
		return g_App->MsgProc(hwnd, msg, wParam, lParam);
	else
		//The messages a window does not handle should be forwarded to the default window
		//procedure, which then handles the message.The Win32 API supplies the default window
		//procedure, which is called DefWindowProc.
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

AwesomeEngineApp::AwesomeEngineApp( const std::wstring& name, int width, int height, bool vSync )
	: DirectXApp( name, width, height, vSync )
{
	m_LogoImage = nullptr;
	m_hAppInstance = nullptr;
	m_hAppWnd = NULL; //we don't have a window yet
	m_ClientWidth = 800;
	m_ClientHeight = 600;
	m_AppTitle = "Game Engine Dev";
	m_WndStyle = WS_OVERLAPPEDWINDOW; //basic maximize, minimize, etc.. 
	g_App = this;
}

AwesomeEngineApp::~AwesomeEngineApp()
{
	if (m_LogoImage)
		delete m_LogoImage;

	GdiplusShutdown(gdiplusToken);
}

bool AwesomeEngineApp::Initialize()
{
	bool isInit = DirectXApp::Initialize();
	if (isInit)
	{
		mWorld.getSystemManager().addSystem<PhysicsSystem>();
		mWorld.getSystemManager().addSystem<LuaScriptSystem>();
		mWorld.getSystemManager().addSystem<RenderingSystem>();
	}

	return isInit;
}

void AwesomeEngineApp::OnUpdate(UpdateEventArgs& e)
{
	DirectXApp::OnUpdate( e );

	mWorld.update();

	// TODO : polish entity component system
	mWorld.getSystemManager().getSystem<PhysicsSystem>().Update(e.ElapsedTime);
	mWorld.getSystemManager().getSystem<LuaScriptSystem>().Update(e.ElapsedTime);
	mWorld.getSystemManager().getSystem<RenderingSystem>().Update(e.ElapsedTime);

}

Mix::Entity AwesomeEngineApp::CreateEntity()
{
	return mWorld.createEntity();
}


int AwesomeEngineApp::Run()
{
	//step3: A Windows application follows an event-driven programming model.
	//An event can be generated in a number of ways:key presses, mouse clicks,
	//and when a window is created, resized, moved, closed, minimized, maximized, or becomes visible.
	//When an event occurs, Windows sends a message to the application the event
	//occurred for, and adds the message to the application?™s message queue
	//The application constantly checks the message queue for messages in a message loop

	//Main Message Loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		//when the application receives a message, it dispatches the message to the window procedure of the particular window the message is for
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) //peek and remove from the stack
		{
			TranslateMessage(&msg);  //Translates virtual-key messages (alt + ctrl + escape..) into character messages. WM_KEYDOWN and WM_KEYUP combinations produce a WM_CHAR
			DispatchMessage(&msg);   //Dispatches a message to a window procedure (MainWndProc).
		}
	}

	return static_cast<int>(msg.wParam);
}
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
void displayProcessorArchitecture(SYSTEM_INFO &stInfo)
{
	std::cout << "CPU : ";
	switch (stInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL: //0-(x86)
		//printf("Processor Architecture: Intel x86\n");
		std::cout << "Intel x86"; 
		break;
	case PROCESSOR_ARCHITECTURE_ARM: //5-ARM processor type
		std::cout << L"ARM";
		break;
	default:
		//printf("Unknown processor architecture\n");
		std::cout << "Unknown Architecture";
	}

	std::cout << std::endl;
}



bool CheckMemory(const DWORDLONG physicalRAMNeededInMB, const DWORDLONG virtualRAMNeededInMB)
{
	MEMORYSTATUSEX status = { sizeof status };
	GlobalMemoryStatusEx(&status);


	status.ullTotalPhys = status.ullTotalPhys / (1024 * 1024 * 1024);		// GB
	status.ullAvailPhys = status.ullAvailPhys / (1024 * 1024);				// MB
	status.ullTotalVirtual = status.ullTotalVirtual / (1024 * 1024 * 1024);	// GB
	status.ullAvailVirtual = status.ullAvailVirtual / (1024 * 1024);		// MB

	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile / (1024 * 1024);	// MB
	DWORDLONG availVirtualMem = memInfo.ullAvailPageFile / (1024 * 1024);	// MB

	std::cout << "Total physics physics = " << status.ullTotalPhys << " GB" << std::endl;
	std::cout << "Current Physical Memory Available: " << status.ullAvailPhys / 1024 << "GB" << std::endl;
	std::cout << "Total virtual memory = " << totalVirtualMem / 1024 << " GB" << std::endl;
	std::cout << "Current Virtual Memory Available: " << availVirtualMem / 1024 << "GB" << std::endl;

	if (status.ullAvailPhys < physicalRAMNeededInMB)
	{
		std::ostringstream msg;
		msg << "CheckMemory Failure: " << physicalRAMNeededInMB << "MB Required" << std::endl << "Memory Available: " << status.ullAvailPhys << "MB" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "Not Enough Memory", 0);
		return false;
	}

	if (availVirtualMem < virtualRAMNeededInMB)
	{
		std::ostringstream msg;
		msg << "CheckMemory Failure: " << virtualRAMNeededInMB << "MB Required" << std::endl << "Memory Available: " << status.ullAvailVirtual << "MB" << std::endl;

		MessageBoxA(NULL, msg.str().c_str(), "Not Enough Virtual Memory", NULL);
		return false;
	}

	
	return true;

}

LPSTR GetRegistry(LPCSTR StringName)
{
	DWORD dwType = REG_SZ;
	HKEY hKey = 0;
	char value[1024];
	DWORD value_length = 1024;
	LPCSTR subkey = _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
	RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
	RegQueryValueEx(hKey, StringName, NULL, &dwType, (LPBYTE)&value, &value_length);
	std::wcout << "CPU Type : " << value << std::endl;
	return  value;
}

DWORD AwesomeEngineApp::ReadCPUSpeed()
{
	DWORD dwMHz = 0;
	HKEY hKey;
	//open key where proc speed is hidden
	std::string myString = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";

	LPCSTR result = myString.c_str();

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		result,
		0,
		KEY_READ,
		&hKey);

	if (lError == ERROR_SUCCESS)
	{
		DWORD dwLen = 4;
		if (RegQueryValueEx(hKey, _T("~MHz"), NULL, NULL, (LPBYTE)&dwMHz, &dwLen) != ERROR_SUCCESS)
		{
			return 0;
		}
		RegCloseKey(hKey);
	}

	GetRegistry(_T("ProcessorNameString"));
	
	return dwMHz;
}

Image* g_LogoImage = nullptr;
bool g_Initialized = false;
std::mutex g_mutex;
void DiminishLogo()
{
	if (g_Initialized == false)
	{
		static const auto start = std::chrono::system_clock::now();
		const auto now = std::chrono::system_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() > 3.0f)
			g_Initialized = true;;

		if (g_Initialized)
		{
			delete g_LogoImage;
			g_LogoImage = nullptr;

		}
	}
}

bool AwesomeEngineApp::CheckRequirements(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	if (!IsOnlyInstance(_T("test")))
	{
		MessageBox(NULL, _T("the game has multiple instances"), _T("ERROR"), 0);
		return false;
	}

	// Ask for 100 GB
	if (!CheckStorage(diskRequiredInMB))
	{
		return false;
	}

	// First variable passed in is total RAM needed (in GB), second is total virtual RAM needed (also in GB)
	if (!CheckMemory(memoryRequiredInMB, virtualMemoryRequriedInMB))
	{
		return false;
	}


	if (!InitWindow())
	{
		return false;
	}

	//Checks if system has minimum of 500Mhz CPU Speed.
	DWORD cpuSpeed = ReadCPUSpeed();

	if (cpuSpeed < cpuSpeedRequiredInMHz)
	{
		std::ostringstream msg;
		msg << "Check CPU failed, below required minimum of: "<< cpuSpeedRequiredInMHz << "Mhz" << std::endl << "Actual: " << cpuSpeed << "Mhz" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "CPU Requirements Check!", 0); 
	}
	else {
		std::cout << "Check CPU Speed Okay" << std::endl << "CPU Speed: " << cpuSpeed << "Mhz" << std::endl;
	}

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	SYSTEM_INFO stInfo;
	GetSystemInfo(&stInfo);
	//displayProcessorArchitecture(stInfo);

	g_LogoImage = Gdiplus::Image::FromFile(s2ws(".\\Assets\\loadingImage.jpg").c_str());

	return true;
}

bool AwesomeEngineApp::InitWindow()
{
	static TCHAR szWindowClass[] = _T("DXAPPWNDCLASS");
	static TCHAR szTitle[] = _T("Game Engine Dev");


	//WNDCLASSEX - Bear in mind that the only difference between CreateWindow and CreateWindowEx is the addition of extended styles to the latter. You can use either type of window class structure with them.
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX)); //Fills a block of memory with zeros.
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = m_hAppInstance;
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(0, IDC_ARROW); 
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;

	//register with Windows OS
	if (!RegisterClassEx(&wcex))
	{
		//OutputDebugString(L"Failed to create Window Class\n");
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Awesome Engine"),
			NULL);
		return false;
	}


	RECT r = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect(&r, m_WndStyle, FALSE);
	UINT width = r.right - r.left;
	UINT height = r.bottom - r.top;
	UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics(SM_CXSCREEN) / 2 - height;
	//step1 we use WIN32 API to create window - when using 16-bit wide-characters (unicode), we must prefix a string literal with a capital L!
	m_hAppWnd = CreateWindow(szWindowClass, szTitle, m_WndStyle, x, y, width, height, NULL, NULL, m_hAppInstance, NULL);

	if (!m_hAppWnd) {
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Awesome Engine"),
			NULL);
		return false; 
	}

	//step2 to notify Windows to show a particular window. Note that Windows applications do not have direct access to hardware.
	//For example, to display a window you must call the Win32 API function ShowWindow; you cannot write to video memory directly.
	ShowWindow(m_hAppWnd, SW_SHOW); 
	UpdateWindow(m_hAppWnd);

	//InitLuaScript();

	EventListenerDelegate mouseMoveListener(this, &AwesomeEngineApp::EventMouseMoved);
	EventManager::GetInstance().VAddListener(mouseMoveListener, EnumEventType::Event_Mouse_Moved);

	EventListenerDelegate mouseClickListener(this, &AwesomeEngineApp::EventMouseClicked);
	EventManager::GetInstance().VAddListener(mouseClickListener, EnumEventType::Event_Mouse_Clicked);

	EventListenerDelegate keyDownListener(this, &AwesomeEngineApp::EventKeyPressed);
	EventManager::GetInstance().VAddListener(keyDownListener, EnumEventType::Event_CharKey_Pressed);


	return true;
}


//step5: Once upon a time, Windows was 16 - bit.Each message could carry with it two pieces of data, called WPARAMand LPARAM.The first one was a 16 - bit value(?œword??, so it was called W.The second one was a 32 - bit value(?œlong??, so it was called L.
//You used the W parameter to pass things like handles and integers.You used the L parameter to pass pointers.
//When Windows was converted to 32 - bit, the WPARAM parameter grew to a 32 - bit value as well.So even though the ?œW??stands for ?œword?? it isn?™t a word any more. (And in 64 - bit Windows, both parameters are 64 - bit values!)

//typedef LONG_PTR LRESULT
static char eventType[100] = _T("");
LRESULT AwesomeEngineApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	char CurrentKeyDown = wParam;

	PAINTSTRUCT ps;
	HDC hdc;

	DiminishLogo();
	

	static size_t messageLength = 0;

	//step6: For instance, we may want to destroy a window when the Escape key is pressed.
	switch (msg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(m_hAppWnd, &ps);
		
		// End application specific layout section.  
		//drawImage(hdc, imageDC);


		Graphics graphics(hdc);
		RECT rect;
		GetWindowRect(hwnd, &rect);

		if (g_LogoImage)
		{
			RectF destRect(0, 0, ( rect.right - rect.left ), ( rect.bottom - rect.top ));
			graphics.DrawImage(g_LogoImage, destRect, 0, 0, g_LogoImage->GetWidth(), g_LogoImage->GetHeight(), Gdiplus::Unit::UnitPixel );
		}
		else
		{
			graphics.Clear(Gdiplus::Color::White);
			TextOut(hdc,
				5, 5,
				eventType, _tcslen(eventType));
		}

		// in the top left corner.  
		
		EndPaint(m_hAppWnd, &ps);
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(m_hAppWnd);
		AwesomeEngine::EventManager::GetInstance().VTriggerEvent(EnumEventType::Event_CharKey_Pressed, { 0, CurrentKeyDown });
		InvalidateRect(m_hAppWnd, NULL, true);
		break;

	case WM_KEYUP:
		AwesomeEngine::EventManager::GetInstance().VTriggerEvent(EnumEventType::Event_CharKey_Pressed, { 1, CurrentKeyDown });
		InvalidateRect(m_hAppWnd, NULL, true);
		break;
	case WM_MOUSEMOVE:
		AwesomeEngine::EventManager::GetInstance().VTriggerEvent(EnumEventType::Event_Mouse_Moved, { xPos, yPos });
		InvalidateRect(m_hAppWnd, NULL, true);
		//swprintf(&eventType[0], _T("Mouse x : %d, y : %d\n"), xPos, yPos );
		
		break;
	case WM_LBUTTONDOWN:
		AwesomeEngine::EventManager::GetInstance().VTriggerEvent(EnumEventType::Event_Mouse_Clicked, { 0, 0 });
		InvalidateRect(m_hAppWnd, NULL, true);
		//swprintf(&eventType[0], _T("Left Button pressed\n"));
		
		break;
	case WM_RBUTTONDOWN:
		AwesomeEngine::EventManager::GetInstance().VTriggerEvent(EnumEventType::Event_Mouse_Clicked, { 1, 0 });
		InvalidateRect(m_hAppWnd, NULL, true);
		//swprintf(&eventType[0], _T("Right Button pressed\n"));
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);  //Indicates to the system that a thread has made a request to terminate
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam); //wParam, lParam..mouse position..ket down...
	}
	return 0;
}

bool AwesomeEngineApp::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(NULL, gameTitle);
		if (hWnd)
		{
			// An instance of your game is already running. 
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}

bool AwesomeEngineApp::CheckStorage(const DWORDLONG diskSpaceNeededInMB)
{
	// Check for enough free disk space on the current disk. 
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const bytes_per_cluster = diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
	unsigned __int64 const neededClusters = (diskSpaceNeededInMB / bytes_per_cluster) * 1024 * 1024;

	unsigned __int64 const avaliableSpaces = (unsigned __int64)
		((double)diskfree.avail_clusters / 1024.0 / 1024.0 * (double)bytes_per_cluster);

	if (diskfree.avail_clusters < neededClusters)
	{
		std::ostringstream msg;
		msg << "CheckStorage Failure: Not enough physical storage. only has " << avaliableSpaces << "MB in the disk" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "ERROR", 0);
		return false;
	}
	else
	{
		std::cout << "CheckStorage Success: " << (avaliableSpaces / 1024) << "GB in the disk available" << std::endl;
		return true;
	}
}


// Event Listener

void AwesomeEngineApp::EventMouseMoved(EventParam param)
{
	//std::cout << "Mouse moved x = " << param.param1 << " " << param.param2 << std::endl;
	sprintf(&eventType[0], _T("Mouse x : %d, y : %d             "), param.param1, param.param2);
}

void AwesomeEngineApp::EventMouseClicked(const EventParam param)
{
	//std::cout << "Mouse clicked x = " << param.param1 << " " << param.param2 << std::endl;
	if( param.param1 == 0 )
		sprintf(&eventType[0], _T("Left Button pressed           "));
	else if (param.param1 == 1)
		sprintf(&eventType[0], _T("Right Button pressed          "));
}

void AwesomeEngineApp::EventKeyPressed(const EventParam param)
{
	//std::cout << "Mouse clicked x = " << param.param1 << " " << param.param2 << std::endl;
	if (param.param1 == 0)
		sprintf(&eventType[0], _T("%c key down                   "), (char)param.param2);
	else if (param.param1 == 1)
		sprintf(&eventType[0], _T("%c key up                     "), (char)param.param2);
}


void AwesomeEngineApp::InitLuaScript()
{
	lua_State* L = luaL_newstate();
	luaL_dofile(L, "Scripts/TestScript.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);
	LuaRef s = getGlobal(L, "testString");
	LuaRef n = getGlobal(L, "number");
	std::string luaString = s.cast<std::string>();
	int answer = n.cast<int>();
	std::cout << luaString << std::endl;
	std::cout << "And here's our number:" << answer << std::endl;

}
//