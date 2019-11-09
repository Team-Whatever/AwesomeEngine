#pragma once
#include <string>

namespace AwesomeEngine
{
	class IJoystickHandler {
		const std::string &buttonName = 0;
		virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
		virtual bool VOnButtonUp(const std::string &buttonName) = 0;
		virtual bool VOnJoystick(float const x, float const y) = 0;
	};
}