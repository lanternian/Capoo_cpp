#include "CapooManager.h"

CapooManager::CapooManager():items(0)
{
}

CapooManager::~CapooManager()
{

}

void CapooManager::add(CapooEntity *capoo)
{
    capooList.push_front(capoo);
    items++;
    cur_capoo = capoo;
}

void CapooManager::clear()
{
    if(capooList.empty()) return;
    for (CapooEntity* capoo : capooList) {
        delete capoo;
    }
    capooList.clear(); // Clear the list to avoid dangling Pointers.
    items = 0;
    cur_capoo = nullptr;
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
void CapooManager::handleInput(sf::Event &event)
{
    for (it = capooList.begin(); it != capooList.end(); it++)
    {
        (*it)->handleInput(event);
    } 
}
