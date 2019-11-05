#pragma once


namespace AwesomeEngine
{
	class IKeyboardHandler {
		virtual bool VOnKeyDown(unsigned int const kcode) = 0;
		virtual bool VOnKeyUp(unsigned int const kcode) = 0;
	};
}