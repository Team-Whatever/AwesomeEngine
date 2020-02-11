// GameMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
//#include "Game/EscapeTheQ.h"
//
//int CALLBACK WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow
//)
//{
//	EscapeTheQ tApp(GetModuleHandle(NULL));
//	if (!tApp.Init(100, 100, 1024, 2000))
//		return 1;
//
//	return tApp.Run();
//}


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include <Shlwapi.h>

#include <Application.h>
#include <dxgidebug.h>

#include "Game/GameApp.h"

void ReportLiveObjects()
{
	IDXGIDebug1* dxgiDebug;
	DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));

	dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_IGNORE_INTERNAL);
	dxgiDebug->Release();
}

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
	int retCode = 0;

	WCHAR path[MAX_PATH];

	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);
	if (argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			// -wd Specify the Working Directory.
			if (wcscmp(argv[i], L"-wd") == 0)
			{
				wcscpy_s(path, argv[++i]);
				SetCurrentDirectoryW(path);
			}
		}
		LocalFree(argv);
	}

	Application::Create(hInstance);
	{
		std::shared_ptr<GameApp> demo = std::make_shared<GameApp>(L"Escape The Q", 1280, 720, true);
		retCode = Application::Get().Run(demo);
	}
	Application::Destroy();

	atexit(&ReportLiveObjects);

	return retCode;
}
