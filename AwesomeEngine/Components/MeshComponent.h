#pragma once
#include <string>

#include "BaseComponent.h"

namespace AwesomeEngine
{
	struct MeshComponent : BaseComponent
	{
		MeshComponent() {}

		// Path to mesh
		std::string mesh;

		// Path to shader
		std::string vertexShader;
		std::string fragmentShader;

		// Constructor
		MeshComponent(std::string const _model, std::string const _vertexShader, std::string const _fragmentShader)
			: mesh(_model), vertexShader(_vertexShader), fragmentShader(_fragmentShader) {}
	};
}
