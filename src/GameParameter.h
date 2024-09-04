#ifndef GAMEPARAMETER_H
#define GAMEPARAMETER_H

#include <iostream>
#include <fstream>
#include <json/json.h>

enum EnumParameter{
    idleTimeMin,

    idleTimeMax,

    hungryProbability,

    pooProbability,

    idleProbability,

    walkProbability,

    runProbability,

    wildProbability,

    walkSpeed,

    runSpeed,

    wildSpeed,

    walkRadius,

    runRadius,

    wildRadius,

    stayActionNumberMax,

    stayActionDuration,

    displayCharacterMaxNumber,

    countGameTimeInterval,

    maxGachaCount,
};

class GameParameter
{
public:
    GameParameter(const GameParameter&) = delete;
    GameParameter& operator=(const GameParameter&) = delete;
	static GameParameter &getInstance()
	{
		static GameParameter instance;
		return instance;
	}

    int getParameter(std::string p);

private:
    GameParameter();
    ~GameParameter();

    Json::Value root;
};

#endif
