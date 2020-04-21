#pragma once
#include "Libs/rapidjson/rapidjson.h"
#include "Libs/rapidjson/document.h"

#include <string>
#include <DirectXMath.h>


namespace Mix
{
	class World;
	class Entity;
}

namespace AwesomeEngine
{
	class SceneLoader
	{

	public:
		void LoadScene( Mix::World& world, std::string sceneFileName );

	private:
		void LoadObject( Mix::World& world, const rapidjson::Value& obj );
		void LoadComponents(Mix::World& world, Mix::Entity& entity, const rapidjson::Value& comps);
		void LoadPrimitives( Mix::Entity& entity, std::string primitiveType );
		void LoadTransform(Mix::Entity& entity, const rapidjson::Value& obj);
		void LoadChildObject(Mix::World& world, Mix::Entity& entity, const rapidjson::Value& obj);
		DirectX::FXMVECTOR LoadVector(const rapidjson::Value& obj);

	private:
		
	};
}