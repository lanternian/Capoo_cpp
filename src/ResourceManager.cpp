#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

SpineData* ResourceManager::addData(Type t, const std::string &name, float scale)
{
    std::string folder;
    switch (t)
    {
	case Type::BODY:
        folder = "body";
        break;
	case Type::EFX_BOT:
        folder = "efx_bot";
        break;
	case Type::CAPOO_ACC_BOT:
        folder = "capoo_acc_bot";
        break;
	case Type::FACE:
        folder = "face";
        break;
	case Type::FACE_DECORATION:
        folder = "mask";
        break;
	case Type::HAT:
        folder = "hat";
        break;
	case Type::CLOTHES:
        folder = "clothes";
        break;
	case Type::BACK:
        folder = "back";
        break;
	case Type::RIGHT_HAND_ITEM:
        folder = "prop_r";
        break;
	case Type::MOOD:
        folder = "mood";
        break;
	case Type::CAPOO_ACC_BODY:
        folder = "capoo_acc_body";
        break;
	case Type::CAPOO_ACC_TOP:
        folder = "capoo_acc_top";
        break;
	case Type::EFX_TOP:
        folder = "efx_top";
        break;
	case Type::EFX_APPEARS:
        folder = "efx_appear";
        break;
	case Type::TALK:
        folder = "talk";
        break;
	case Type::FOOD:
        folder = "food";
        break;
	case Type::POO:
        folder = "poo";
        break;   
    default:
        std::cerr << "Error: Unrecognized Type enum value." << std::endl;
        break;
    }

    std::string jsonName = std::format("data/spine/{}/{}.json", folder, name);
    std::string atlasName = std::format("data/spine/{}/{}.atlas.txt", folder, name);
    try {
        data[t].insert(std::make_pair(name,std::make_unique<SpineData>(jsonName.c_str() , atlasName.c_str(), scale)));
        return data[t][name].get();
    } catch (const std::bad_alloc& e) {
        std::cerr << "Failed to allocate memory: " << e.what() << std::endl;
        return nullptr;
    }
}

SpineData* ResourceManager::getData(Type t, const std::string &name)
{
    auto& umap = data[t];
    auto it = umap.find(name);
    if (it != umap.end()) {
        return it->second.get();
    } else {
        return addData(t,name,0.5);
    }
}

bool ResourceManager::removeData(Type t, const std::string &name)
{
    auto& umap = data[t];  
    auto it = umap.find(name);  
    if (it != umap.end()) {
        umap.erase(it); 
        return true;  
    } else {
        return false;  
    }
}

