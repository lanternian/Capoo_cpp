#include "CapooManager.h"

CapooManager::CapooManager():items(0)
{
}

CapooManager::~CapooManager()
{
    clear();
}

void CapooManager::add(CapooEntity *capoo)
{
    capooList.push_front(capoo);
    items++;
}

void CapooManager::clear()
{
    for (CapooEntity* capoo : capooList) {
        delete capoo;
    }
}

void CapooManager::update(float deltaTime)
{
    for (it = capooList.begin(); it != capooList.end(); it++)
    {
        (*it)->update(deltaTime);
    }
    
}
void CapooManager::draw(sf::RenderWindow *window)
{
    for (it = capooList.begin(); it != capooList.end(); it++)
    {
        (*it)->draw(window);
    }
}
