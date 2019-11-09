#pragma once
#include <DirectXMath.h>
#include <string>

namespace AwesomeEngine
{
	class IPointerHandler {
	public:
		virtual bool VOnPointerMove(const FXMVECTOR &mousePos) = 0;
		virtual bool VOnPointerButtonDown(const FXMVECTOR& mousePos, const std::string &buttonName) = 0;
		virtual bool VOnPointerButtonUp(const FXMVECTOR& mousePos, const std::string &buttonName) = 0;
		virtual int VGetPointerRadius() = 0;
	};
}