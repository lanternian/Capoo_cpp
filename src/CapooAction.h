#ifndef CAPOOACTION_H
#define CAPOOACTION_H

#include <iostream>
#include <fstream>
#include <json/json.h>

class CapooAction
{
public:
    CapooAction(const CapooAction&) = delete;
    CapooAction& operator=(const CapooAction&) = delete;
	static CapooAction &getInstance()
	{
		static CapooAction instance;
		return instance;
	}

    Json::Value getAnime(std::string name) const;


private:
    CapooAction();
    ~CapooAction();

    Json::Value root;
};

#endif