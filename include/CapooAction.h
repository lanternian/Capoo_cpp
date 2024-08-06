#ifndef CAPOOACTION_H
#define CAPOOACTION_H

#include <iostream>
#include <fstream>
#include <json/json.h>

enum CapooActionNameKey
{
	idle_idle,
	idle_full,
	walk,
	run,
	wild,
	roll,
	air,
	fall,
	hit,
	pet,
	prone,
	catchUp,
	stackFog,
	stackDown,
	foodAppear,
	chew,
	enjoy,
	pooing,
	waitCleanPoo,
	pooRemoving,
	pooRemoveAfter,
	dizzy,
	summonAppear,
	recycle,
	merge
};

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