
#include "DXApp.h"
#include <iostream>
#include <sstream>
#include <direct.h>
#include <string.h>


namespace {
	//used to forward messages to user defined proc function
	DXApp* g_App = nullptr;
}

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

DXApp::DXApp(HINSTANCE hInstance)
{
	m_hAppInstance = hInstance;
	m_hAppWnd = NULL; //we don't have a window yet
	m_ClientWidth = 800;
	m_ClientHeight = 800;
	m_AppTitle = "DirectX12 Application";
	m_WndStyle = WS_OVERLAPPEDWINDOW; //basic maximize, minimize, etc.. 
	g_App = this;
}

DXApp::~DXApp()
{
}

int DXApp::Run()
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
		else
		{
			//In off-time we update and render
			Update(0.0);
			Render(0.0);
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


#define DIV 1024
#define WIDTH 7

bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status = { sizeof status };
	GlobalMemoryStatusEx(&status);

	status.ullTotalPhys = status.ullTotalPhys / (1024 * 1024 * 1024);
	status.ullAvailPhys = status.ullAvailPhys / (1024 * 1024 * 1024);

	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile / (1024 * 1024 * 1024);
	DWORDLONG availVirtualMem = memInfo.ullAvailPageFile / (1024 * 1024 * 1024);
		

	status.ullTotalPhys = status.ullTotalPhys / (1024 * 1024 * 1024);		// GB
	status.ullAvailPhys = status.ullAvailPhys / (1024 * 1024);				// MB
	status.ullTotalVirtual = status.ullTotalVirtual / (1024 * 1024 * 1024);	// GB
	status.ullAvailVirtual = status.ullAvailVirtual / (1024 * 1024);		// MB

	std::cout << "Total physics physics = " << status.ullTotalPhys << " GB" << std::endl;
	std::cout << "Current Physical Memory Available: " << status.ullAvailPhys / 1024 << "GB" << std::endl;
	std::cout << "Total virtual memory = " << status.ullTotalVirtual << " GB" << std::endl;
	std::cout << "Current Virtual Memory Available: " << status.ullAvailVirtual / 1024 << "GB" << std::endl;

	if (status.ullAvailPhys < physicalRAMNeeded )
	{
		std::ostringstream msg;
		msg << "CheckMemory Failure: " << physicalRAMNeeded << "MB Required" << std::endl << "Memory Available: " << status.ullAvailPhys << "MB" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "Not Enough Memory", 0);
		return false;
	}

	if (availVirtualMem < virtualRAMNeeded)
	{
		std::ostringstream msg;
		msg << "CheckMemory Failure: " << virtualRAMNeeded << "MB Required" << std::endl << "Memory Available: " << status.ullAvailVirtual << "MB" << std::endl;

		MessageBoxA(NULL, msg.str().c_str(), "Not Enough Virtual Memory", NULL);
		return false;
	}

	
		MessageBox(NULL, L"CheckMemory Failure: Not enough virtual memory", L"Memory", NULL);
		return false; 
	}

	std::ostringstream msg;
	msg << "Current Virtual Memory Available: " << availVirtualMem << "GB" << std::endl << "Current Physical Memory Available: " << status.ullAvailPhys << "GB" << std::endl;
	MessageBoxA(NULL, msg.str().c_str(), "Memory", 0);

	return true;

}

LPWSTR GetRegistry(LPCWSTR StringName)
{
	DWORD dwType = REG_SZ;
	HKEY hKey = 0;
	TCHAR value[1024];
	DWORD value_length = 1024;
	LPCWSTR subkey = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
	RegQueryValueEx(hKey, StringName, NULL, &dwType, (LPBYTE)&value, &value_length);
	std::wcout << "CPU Type : " << value << std::endl;
	return  value;
}

DWORD DXApp::ReadCPUSpeed()
{
	DWORD dwMHz = 0;
	HKEY hKey;
	//open key where proc speed is hidden
	std::string myString = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";

	std::wstring stemp = s2ws(myString);
	LPCWSTR result = stemp.c_str();

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		result,
		0,
		KEY_READ,
		&hKey);

	if (lError == ERROR_SUCCESS)
	{
		DWORD dwLen = 4;
		if (RegQueryValueEx(hKey, L"~MHz", NULL, NULL, (LPBYTE)&dwMHz, &dwLen) != ERROR_SUCCESS)
		{
			return 0;
		}
		RegCloseKey(hKey);
	}

	GetRegistry(L"ProcessorNameString");
	
	return dwMHz;
}


bool DXApp::Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	if (!IsOnlyInstance(L"test"))
	{
		MessageBox(NULL, L"the game has multiple instances", L"ERROR", 0);
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

	SYSTEM_INFO stInfo;
	GetSystemInfo(&stInfo);
	//displayProcessorArchitecture(stInfo);

	return true;
}


bool DXApp::InitWindow()
{
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
	wcex.lpszClassName = L"DXAPPWNDCLASS"; 

	//register with Windows OS
	if (!RegisterClassEx(&wcex))
	{
		OutputDebugString(L"Failed to create Window Class\n");
		return false;
	}

	RECT r = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect(&r, m_WndStyle, FALSE);
	UINT width = r.right - r.left;
	UINT height = r.bottom - r.top;
	UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics(SM_CXSCREEN) / 2 - height / 2;
	//step1 we use WIN32 API to create window - when using 16-bit wide-characters (unicode), we must prefix a string literal with a capital L!
	m_hAppWnd = CreateWindow(L"DXAPPWNDCLASS", L"test", m_WndStyle, x, y, width, height, NULL, NULL, m_hAppInstance, NULL);

	if (!m_hAppWnd) {
		OutputDebugString(L"Failed to create Window \n");
		return false; 
	}



	//step2 to notify Windows to show a particular window. Note that Windows applications do not have direct access to hardware.
	//For example, to display a window you must call the Win32 API function ShowWindow; you cannot write to video memory directly.
	ShowWindow(m_hAppWnd, SW_SHOW); 

	return true;
}




//step5: Once upon a time, Windows was 16 - bit.Each message could carry with it two pieces of data, called WPARAMand LPARAM.The first one was a 16 - bit value(?œword??, so it was called W.The second one was a 32 - bit value(?œlong??, so it was called L.
//You used the W parameter to pass things like handles and integers.You used the L parameter to pass pointers.
//When Windows was converted to 32 - bit, the WPARAM parameter grew to a 32 - bit value as well.So even though the ?œW??stands for ?œword?? it isn?™t a word any more. (And in 64 - bit Windows, both parameters are 64 - bit values!)

//typedef LONG_PTR LRESULT
LRESULT DXApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//step6: For instance, we may want to destroy a window when the Escape key is pressed.
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(m_hAppWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);  //Indicates to the system that a thread has made a request to terminate
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam); //wParam, lParam..mouse position..ket down...
	}

}

bool DXApp::IsOnlyInstance(LPCTSTR gameTitle)
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

bool DXApp::CheckStorage(const DWORDLONG diskSpaceNeededInMB)
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

