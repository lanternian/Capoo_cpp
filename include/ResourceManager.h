#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <format>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "SpineData.h"
#include "Constants.h"

// singleton pattern.
class ResourceManager
{
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
	static ResourceManager &getInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	SpineData* addData(Type t, const std::string &name, float scale = 0.5);
	SpineData* getData(Type t, const std::string &name);
	bool removeData(Type t, const std::string &name);
	

private:
	ResourceManager();
	~ResourceManager();

	std::unordered_map<std::string, std::unique_ptr<SpineData>> data[TOTAL];
};

#endif