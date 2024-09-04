#include "globalVar.h"

#include "Game.h"

CapooInfo &info_table = CapooInfo::getInstance();
CapooAction &action_table = CapooAction::getInstance();
GameParameter &parameter_table = GameParameter::getInstance();

int mint = parameter_table.getParameter("idleTimeMin");
int maxt = parameter_table.getParameter("idleTimeMax");
float capooPetHoverDuration = 1.5f;

int getRandomInt(int a, int b) // [a,b)
{
    if (a >= b) {
        throw std::invalid_argument("Upper bound must be greater than lower bound.");
    }

    return rand() % (b-a) + a;
}

int getRandomInt(int b) // [0,b)
{
    int a = 0;
    if (a >= b) {
        throw std::invalid_argument("Upper bound must be greater than lower bound.");
    }

    return rand() % (b-a) + a;
}