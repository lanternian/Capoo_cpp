#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "SpineData.h"
#include "SpineEntity.h"
#include "CapooEntity.h"
#include "ResourceManager.h"
#include "CapooInfo.h"
#include "CapooManager.h"

class Game
{
public:
    Game();
    ~Game();
    float getAbsolutTime();
    void init();
    void startGame();
    void processInput();
    void update();
    void render();
    void quit();
    
    sf::RenderWindow &getWindow() const{ return *mainwindow; }
private:
    sf::RenderWindow *mainwindow;
    int screenWidth;
    int screenHeight;
    float lastTime;

    

};

Game& game();

#endif
