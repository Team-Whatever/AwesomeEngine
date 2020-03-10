#pragma once

#include <DirectXMath.h>
#include "BaseComponent.h"

namespace AwesomeEngine
{
	struct TransformComponent : BaseComponent
	{

		TransformComponent(DirectX::XMVECTOR _pos = DirectX::XMVectorSet( 0, 0, 0, 0), 
			DirectX::XMVECTOR _scale = DirectX::XMVectorSet(1, 1, 1, 1),
			DirectX::XMVECTOR _angle = DirectX::XMVectorSet(0, 0, 0, 0))
			: position( _pos ), scale( _scale ), rotation( _angle )
		{
		}


		DirectX::XMVECTOR position;
		DirectX::XMVECTOR scale;
		DirectX::XMVECTOR rotation;
	};
}