#include "CapooAction.h"

CapooAction::CapooAction()
{
    std::ifstream file("data/json/Capoo_Action.json", std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file 'data/json/Capoo_Action.json'");
        return;
    }
    file >> root;
}

CapooAction::~CapooAction()
{

}

Json::Value CapooAction::getAnime(std::string action_name) const
{
    for(auto a:root){
        if(a["action_name"]==action_name)
            return a;
    }
    return NULL;
}