#include "CapooInfo.h"

CapooInfo::CapooInfo()
{
    std::ifstream file("data/json/Capoo_Info.json", std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file 'data/json/Capoo_Info.json'");
        return;
    }
    file >> root;
}

CapooInfo::~CapooInfo()
{

}

Json::Value CapooInfo::getID(int id) const 
{
    return root[id-1];
}

Json::Value CapooInfo::getID(std::string idStr) const
{
    int id = std::stoi(idStr.substr(idStr.size() - 3));
    return getID(id);
}

void CapooInfo::printInfo(int id) const
{
    Json::Value capoo = getID(id);
    std::cout << "ID: " << capoo["id"].asString() << std::endl;
    std::cout << "Name: " << capoo["name"].asString() << std::endl;
    std::cout << "Collider Adjust: " << capoo["collider_Adjust"].asString() << std::endl;
    std::cout << "Body: " << capoo["body"].asString() << std::endl;
    std::cout << "Face: " << capoo["face"].asString() << std::endl;
    std::cout << "Hat: " << capoo["hat"].asString() << std::endl;
    std::cout << "Mood: " << capoo["mood"].asString() << std::endl;
    std::cout << "Effect Bottom: " << capoo["efx_bot"].asString() << std::endl;
    std::cout << "Effect Top: " << capoo["efx_top"].asString() << std::endl;
    std::cout << "Effect Appears: " << capoo["efx_appears"].asString() << std::endl;
    std::cout << "Talk: " << capoo["talk"].asString() << std::endl;
    std::cout << "Food: " << capoo["food"].asString() << std::endl;
    std::cout << "Poo: " << capoo["poo"].asString() << std::endl;
}

void CapooInfo::printInfo(std::string idStr) const
{
    Json::Value capoo = getID(idStr);
    std::cout << "ID: " << capoo["id"].asString() << std::endl;
    std::cout << "Name: " << capoo["name"].asString() << std::endl;
    std::cout << "Collider Adjust: " << capoo["collider_Adjust"].asString() << std::endl;
    std::cout << "Body: " << capoo["body"].asString() << std::endl;
    std::cout << "Face: " << capoo["face"].asString() << std::endl;
    std::cout << "Hat: " << capoo["hat"].asString() << std::endl;
    std::cout << "Mood: " << capoo["mood"].asString() << std::endl;
    std::cout << "Effect Bottom: " << capoo["efx_bot"].asString() << std::endl;
    std::cout << "Effect Top: " << capoo["efx_top"].asString() << std::endl;
    std::cout << "Effect Appears: " << capoo["efx_appears"].asString() << std::endl;
    std::cout << "Talk: " << capoo["talk"].asString() << std::endl;
    std::cout << "Food: " << capoo["food"].asString() << std::endl;
    std::cout << "Poo: " << capoo["poo"].asString() << std::endl;
}
