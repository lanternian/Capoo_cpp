#include "Game.h"

namespace
{
    Game* gameptr;
}

Game::Game()
{
    gameptr = this;
    mainwindow = new sf::RenderWindow(sf::VideoMode(640, 640), "Spine SFML - capoo");
    std::cout << "create mainwindow" << std::endl;
}

Game::~Game()
{
    delete mainwindow;
    std::cout << "delete mainwindow" << std::endl;
}

float Game::getAbsolutTime()
{
    static sf::Clock clock;
    float ret = clock.getElapsedTime().asSeconds();
    clock.restart();
    return ret;
}

void Game::init()
{
    CapooEntity *a = new CapooEntity();
    CapooManager::getInstance().add(a);

}

void Game::processInput()
{
    static sf::Event event;
    while (mainwindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mainwindow->close();
            
    }
}

void Game::update()
{
    lastTime = getAbsolutTime();
    CapooManager::getInstance().update(lastTime);

}

void Game::render()
{
    mainwindow->clear(sf::Color::White);
    CapooManager::getInstance().draw(mainwindow);
    mainwindow->display();
}

void Game::quit()
{
}

void Game::startGame()
{
    init();

    lastTime = getAbsolutTime();
    
    while (mainwindow->isOpen())
    {
        processInput();
        update();
        render();
    }

    quit();

}

// global function to gain game objection.
Game &game()
{
    return *gameptr;
}