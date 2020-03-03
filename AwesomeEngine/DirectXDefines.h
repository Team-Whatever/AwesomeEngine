#pragma once

#include <DirectXMath.h>
#include "CommandList.h"

namespace AwesomeEngine
{
	struct Mat
	{
		DirectX::XMMATRIX ModelMatrix;
		DirectX::XMMATRIX ModelViewMatrix;
		DirectX::XMMATRIX InverseTransposeModelViewMatrix;
		DirectX::XMMATRIX ModelViewProjectionMatrix;
	};


	// An enum for root signature parameters.
	// I'm not using scoped enums to avoid the explicit cast that would be required
	// to use these as root indices in the root signature.
	enum RootParameters
	{
		MatricesCB,         // ConstantBuffer<Mat> MatCB : register(b0);
		MaterialCB,         // ConstantBuffer<Material> MaterialCB : register( b0, space1 );
		LightPropertiesCB,  // ConstantBuffer<LightProperties> LightPropertiesCB : register( b1 );
		PointLights,        // StructuredBuffer<PointLight> PointLights : register( t0 );
		SpotLights,         // StructuredBuffer<SpotLight> SpotLights : register( t1 );
		Textures,           // Texture2D DiffuseTexture : register( t2 );
		NumRootParameters
	};
}

