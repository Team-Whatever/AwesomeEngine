// GameMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "Game/EscapeTheQ.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	EscapeTheQ tApp(GetModuleHandle(NULL));
	if (!tApp.Init(100, 100, 1024, 2000))
		return 1;

	return tApp.Run();
}
