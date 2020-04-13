#include "SceneLoader.h"
#include "Libs/rapidjson/istreamwrapper.h"
#include "Mix/World.h"
#include "Mix/Entity.h"
#include "Components/TransformComponent.h"
#include "Components/CubeComponent.h"
#include "Components/CylinderComponent.h"
#include "Components/SphereComponent.h"
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
		
		assert(doc["children"].IsObject());
		
		LoadObject( world, doc["children"] );
	}

	void SceneLoader::LoadObject( Mix::World& world, const rapidjson::Value& obj )
	{
		assert(obj.HasMember("$values"));
		if (obj.HasMember("$values"))
		{
			auto values = obj["$values"].GetArray();
			for (auto& val : values)
			{
				std::string childName = val["Name"].GetString();
				std::string childType = val["Type"].GetString();
				if (childType == "UnityEngine.GameObject")
				{
					auto entity = world.createEntity();
					if (val.HasMember("components"))
					{
						LoadComponents(world, entity, val["components"]);
					}
					if (val.HasMember("children"))
					{
						auto childrenArray = val["children"]["$values"].GetArray();
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
				auto childrenArray = obj["children"]["$values"].GetArray();
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
		assert(comps.HasMember("$values"));
		if( comps.HasMember("$values") )
		{
			auto compsArray = comps["$values"].GetArray();
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
				else if (compType == "UnityEngine.MeshFilter")
				{
					std::string meshName = comp["meshName"].GetString();
					if (meshName == "Cube")
					{
						entity.addComponent<CubeComponent>();
					}
					else if (meshName == "Cylinder")
					{
						entity.addComponent<CylinderComponent>();
					}
					else if (meshName == "Sphere")
					{
						entity.addComponent<SphereComponent>();
					}
					//else if (meshName == "Plane")
					//{
					//	entity.addComponent<PlaneComponent>();
					//}

				}
			}
		}
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