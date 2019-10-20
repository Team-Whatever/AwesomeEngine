#pragma once

#include <DirectXMath.h>
#include "BaseComponent.h"

namespace AwesomeEngine
{
	struct TransformComponent : BaseComponent
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