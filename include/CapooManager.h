#ifndef CAPOOMANAGER_H
#define CAPOOMANAGER_H

#include <list>

#include "CapooEntity.h"

class CapooManager
{
public:
    CapooManager(const CapooManager&) = delete;
    CapooManager& operator=(const CapooManager&) = delete;
	static CapooManager &getInstance()
	{
		static CapooManager instance;
		return instance;
	}

    void add(CapooEntity *a);
    void clear();
    void update(float deltaTime);
    void draw(sf::RenderWindow *window);

    typedef std::list<CapooEntity*> CapooList;

    CapooList& getList() {return capooList;}

private:
    CapooManager();
    ~CapooManager();

    CapooList capooList;
    CapooList::iterator it;
    int items;
};

#endif