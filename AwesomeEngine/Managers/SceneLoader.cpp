#include "SceneLoader.h"
#include "Libs/rapidjson/istreamwrapper.h"
#include "Mix/World.h"
#include "Mix/Entity.h"
#include "Components/TransformComponent.h"
#include "Components/CubeComponent.h"
#include "Components/CylinderComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TorusComponent.h"
#include "Components/ConeComponent.h"
#include "Components/PlaneComponent.h"

#include <fstream>
#include <iostream>

using namespace DirectX;
namespace AwesomeEngine
{
	void SceneLoader::LoadScene( Mix::World& world, std::string sceneFileName )
	{
		std::ifstream sceneFS(sceneFileName.c_str());
		rapidjson::IStreamWrapper isw(sceneFS);
		rapidjson::Document doc;
		doc.ParseStream(isw);
		
		std::string sceneName = doc["Name"].GetString();
		LoadObject( world, doc );
	}

	void SceneLoader::LoadObject( Mix::World& world, const rapidjson::Value& obj )
	{
		assert(obj.HasMember("children") && obj["children"].IsArray());
		if (obj.HasMember("children"))
		{
			auto values = obj["children"].GetArray();
			for (auto& val : values)
			{
				auto entity = world.createEntity();

				std::string childName = val["Name"].GetString();
				std::string childType = val["Type"].GetString();
				std::string subType = val["SubType"].GetString();
				if (childType == "Primitive")
				{
					LoadPrimitives( entity, subType );
				}
				if (val.HasMember("transformClass"))
				{
					LoadTransform( entity, val["transformClass"] );
				}
				if (val.HasMember("components"))
				{
					LoadComponents(world, entity, val["components"]);
				}
				if (val.HasMember("children"))
				{
					//LoadChildObject(world, entity, val["children"]);
					//auto childrenArray = val["children"].GetArray();
					//for (auto& child : childrenArray)
					//{
					//	auto childEntity = world.createEntity();
					//	LoadChildObject(world, childEntity, child);

					//	TransformComponent parentTransform = entity.getComponent<TransformComponent>();
					//	TransformComponent childTransform = childEntity.getComponent<TransformComponent>();

					//	XMVECTOR cPos = XMVectorAdd(parentTransform.position, childTransform.position);
					//	XMVECTOR cScale = XMVectorMultiply(parentTransform.scale, childTransform.scale);
					//	XMVECTOR cRotation = XMVectorAdd(parentTransform.rotation, childTransform.rotation);
					//	childEntity.SetLocation(cPos);
					//	childEntity.SetScale(cScale);
					//	childEntity.SetRotation(cRotation);

					//	entity.AddChild(childEntity);
					//}
					
				}
			}
		}
	}

	void SceneLoader::LoadChildObject(Mix::World& world, Mix::Entity& entity, const rapidjson::Value& obj)
	{
		std::string childName = obj["Name"].GetString();
		std::string childType = obj["Type"].GetString();
		if (childType == "UnityEngine.GameObject")
		{
			if (obj.HasMember("components"))
			{
				LoadComponents(world, entity, obj["components"]);
			}
			if (obj.HasMember("children"))
			{
				auto childrenArray = obj["children"].GetArray();
				for (auto& child : childrenArray)
				{
					auto childEntity = world.createEntity();
					LoadChildObject(world, childEntity, child);

					TransformComponent parentTransform = entity.getComponent<TransformComponent>();
					TransformComponent childTransform = childEntity.getComponent<TransformComponent>();

					XMVECTOR cPos = XMVectorAdd(parentTransform.position, childTransform.position);
					XMVECTOR cScale = XMVectorMultiply(parentTransform.scale, childTransform.scale);
					XMVECTOR cRotation = XMVectorAdd(parentTransform.rotation, childTransform.rotation);
					childEntity.SetLocation(cPos);
					childEntity.SetScale(cScale);
					childEntity.SetRotation(cRotation);

					entity.AddChild(childEntity);
				}
			}
		}
	}

	void SceneLoader::LoadComponents(Mix::World& world, Mix::Entity& entity, const rapidjson::Value& comps)
	{
		assert(comps.IsArray());
		auto compsArray = comps.GetArray();
		for (auto& comp : compsArray)
		{
			std::string compType = comp["Type"].GetString();
			if (compType == "UnityEngine.Transform")
			{
				assert(comp.HasMember("position"));
				assert(comp.HasMember("scale"));
				assert(comp.HasMember("rotation"));

				FXMVECTOR position = LoadVector(comp["position"]);
				FXMVECTOR scale = LoadVector(comp["scale"]);
				FXMVECTOR rotation = LoadVector(comp["rotation"]);

				entity.addComponent<TransformComponent>(position, scale, rotation);
			}
		}
	}

	void SceneLoader::LoadPrimitives( Mix::Entity& entity, std::string primitiveType )
	{
		if (primitiveType == "Cube")
		{
			entity.addComponent<CubeComponent>();
		}
		else if (primitiveType == "Cylinder")
		{
			entity.addComponent<CylinderComponent>();
		}
		else if (primitiveType == "Sphere")
		{
			entity.addComponent<SphereComponent>();
		}
		else if (primitiveType == "Cone")
		{
			entity.addComponent<ConeComponent>();
		}
		else if (primitiveType == "Torus")
		{
			entity.addComponent<TorusComponent>();
		}
	}

	void SceneLoader::LoadTransform(Mix::Entity& entity, const rapidjson::Value& obj)
	{
		assert(obj.HasMember("position"));
		assert(obj.HasMember("scale"));
		assert(obj.HasMember("rotation"));

		FXMVECTOR position = LoadVector(obj["position"]);
		FXMVECTOR scale = LoadVector(obj["scale"]);
		FXMVECTOR rotation = LoadVector(obj["rotation"]);

		entity.addComponent<TransformComponent>(position, scale, rotation);
	}

	FXMVECTOR SceneLoader::LoadVector(const rapidjson::Value& obj)
	{
		assert(obj.IsObject());
		assert(obj.HasMember("x"));
		assert(obj.HasMember("y"));
		assert(obj.HasMember("z"));
		return DirectX::XMVectorSet(obj["x"].GetFloat(), obj["y"].GetFloat(), obj["z"].GetFloat(), 0.0f);
	}

}