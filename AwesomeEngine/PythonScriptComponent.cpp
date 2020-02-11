#include "PythonScriptComponent.h"
#include <iostream>
#include <string>

#include <python_include/Python.h>



namespace AwesomeEngine {

	void printMessage(const std::string& s)
	{
		std::cout << s << std::endl;
	}

	void InitializePythonScript(int x) {
		Py_Initialize(); 
	}

	
}

