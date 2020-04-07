#include "SceneLoader.h"
#include "Libs/rapidjson/rapidjson.h"
#include "Libs/rapidjson/document.h"
#include "Libs/rapidjson/istreamwrapper.h"

#include <fstream>
#include <iostream>

namespace AwesomeEngine
{
	void SceneLoader::LoadScene(std::string sceneFileName)
	{

		std::ifstream sceneFS(sceneFileName.c_str());
		rapidjson::IStreamWrapper isw(sceneFS);
		rapidjson::Document doc;
		doc.ParseStream(isw);
		
		std::string sceneName = doc["Name"].GetString();
		
		assert(doc["children"].IsObject());
		if (doc["children"].HasMember("$values"))
		{
			auto values = doc["children"]["$values"].GetArray();
			for (auto& val : values)
			{
				std::string childName = val["Name"].GetString();
			}
		}
		
	}

}