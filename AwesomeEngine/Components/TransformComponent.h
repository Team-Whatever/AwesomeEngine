#pragma once

#include <DirectXMath.h>

namespace AwesomeEngine
{
	struct TransformComponent
	{

		TransformComponent(FXMVECTOR _pos, FXMVECTOR _scale, FXMVECTOR _angle)
			: position( _pos ), scale( _scale ), eulerAngle( _angle )
		{
		}


		FXMVECTOR position;
		FXMVECTOR scale;
		FXMVECTOR eulerAngle;
	};
}