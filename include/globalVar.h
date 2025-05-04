#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

#include "CapooInfo.h"
#include "CapooAction.h"
#include "GameParameter.h"
#include "CapooManager.h"


extern int mint;
extern int maxt;
extern float capooPetHoverDuration;
extern float pushStrength;
extern CapooInfo &info_table;
extern CapooAction &action_table;
extern GameParameter &parameter_table;
extern CapooManager &capoomanager;

extern int getRandomInt(int a, int b);
extern int getRandomInt(int b);


#endif