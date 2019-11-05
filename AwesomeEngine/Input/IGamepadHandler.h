#pragma once
#include <string>

namespace AwesomeEngine
{
	class IGamepadHandler {
		virtual bool VOnTrigger(const std::string &triggerName, float const pressure) = 0;
		virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
		virtual bool VOnButtonUp(const std::string &buttonName) = 0;
		virtual bool VOnDirectionalPad(const std::string &direction) = 0;
		virtual bool VOnThumbstick(const std::string &stickName, float const x, float const y) = 0;
	};
}