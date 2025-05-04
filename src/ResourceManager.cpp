#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    std::string feedurl = "data/images/char_talk_food.png", cleanurl = "data/images/char_talk_broom.png";
    if (!feedButton.loadFromFile(feedurl))
        throw std::string("Unable to load"+feedurl);
    if (!cleanButton.loadFromFile(cleanurl))
        throw std::string("Unable to load"+cleanurl);
}

ResourceManager::~ResourceManager()
{

}

SpineData* ResourceManager::addData(EnumCapooInfo t, const std::string &name, float scale)
{
    std::string folder;
    switch (t)
    {
	case EnumCapooInfo::BODY:
        folder = "body";
        break;
	case EnumCapooInfo::EFX_BOT:
        folder = "efx_bot";
        break;
	case EnumCapooInfo::CAPOO_ACC_BOT:
        folder = "capoo_acc_bot";
        break;
	case EnumCapooInfo::FACE:
        folder = "face";
        break;
	case EnumCapooInfo::FACE_DECORATION:
        folder = "mask";
        break;
	case EnumCapooInfo::HAT:
        folder = "hat";
        break;
	case EnumCapooInfo::CLOTHES:
        folder = "clothes";
        break;
	case EnumCapooInfo::BACK:
        folder = "back";
        break;
	case EnumCapooInfo::RIGHT_HAND_ITEM:
        folder = "prop_r";
        break;
	case EnumCapooInfo::MOOD:
        folder = "mood";
        break;
	case EnumCapooInfo::CAPOO_ACC_BODY:
        folder = "capoo_acc_body";
        break;
	case EnumCapooInfo::CAPOO_ACC_TOP:
        folder = "capoo_acc_top";
        break;
	case EnumCapooInfo::EFX_TOP:
        folder = "efx_top";
        break;
	case EnumCapooInfo::EFX_APPEARS:
        folder = "efx_appear";
        break;
	case EnumCapooInfo::TALK:
        folder = "char_talk";
        break;
	case EnumCapooInfo::FOOD:
        folder = "food";
        break;
	case EnumCapooInfo::POO:
        folder = "poo";
        break;   
    default:
        std::cerr << "Error: Unrecognized EnumCapooInfo enum value." << std::endl;
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

SpineData* ResourceManager::getData(EnumCapooInfo t, const std::string &name)
{
    auto& umap = data[t];
    auto it = umap.find(name);
    if (it != umap.end()) {
        return it->second.get();
    } else {
        return addData(t,name,INIT_SCALE);
    }
}

bool ResourceManager::recapoomoveData(EnumCapooInfo t, const std::string &name)
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

