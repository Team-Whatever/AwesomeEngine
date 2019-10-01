#include <iostream>
#include "TestApp.h"

int main()
{
	TestApp tApp(GetModuleHandle(NULL));
	if (!tApp.Init( 100, 100, 1024, 2000 )) 
		return 1; 

	return tApp.Run();

}