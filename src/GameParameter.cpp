#include "GameParameter.h"

GameParameter::GameParameter()
{
    std::ifstream file("data/json/Game_Parameter.json", std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file 'data/json/Game_Parameter.json'");
        return;
    }
    file >> root;
}

GameParameter::~GameParameter()
{

}

int GameParameter::getParameter(std::string p)
{
    return root[0][p].asInt();
}