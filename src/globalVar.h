#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

#include "CapooInfo.h"
#include "CapooAction.h"
#include "GameParameter.h"


extern int mint;
extern int maxt;
extern float capooPetHoverDuration;
extern CapooInfo &info_table;
extern CapooAction &action_table;
extern GameParameter &parameter_table;

extern int getRandomInt(int a, int b);
extern int getRandomInt(int b);


#endif