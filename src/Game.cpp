#include "Game.h"

#include <windows.h>

void TransparentWindow(sf::RenderWindow *window) {
    // transparent window
    HWND hWnd = window->getSystemHandle();
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

namespace
{
    Game* gameptr;
}

Game::Game()
{
    srand(time(NULL));
    
    gameptr = this;
    mainwindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH-1, WINDOW_HEIGHT-1), "Spine SFML - capoo", sf::Style::None);
    TransparentWindow(mainwindow);
    std::cout << "create mainwindow" << std::endl;
}

Game::~Game()
{
    CapooManager::getInstance().clear();
    delete mainwindow;
    std::cout << "delete mainwindow" << std::endl;
}

float Game::getAbsolutTime()
{
    static sf::Clock clock;
    return clock.getElapsedTime().asSeconds();
}

void Game::init()
{
    CapooEntity *a = new CapooEntity(1, sf::Vector2i(getRandomInt(WINDOW_WIDTH), getRandomInt(WINDOW_HEIGHT)));
    CapooManager::getInstance().add(a);

}

void Game::processInput()
{
    static sf::Event event;
    while (mainwindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed )
            mainwindow->close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Q)
                mainwindow->close();
            if (event.key.code == sf::Keyboard::B) {
                // printf("�����뿧����ţ���1~126��\n");
                // int id;
                // while (!(std::cin >> id) || id < 1 || id > 126) {
                //     std::cin.clear();
                //     std::cin.ignore(10000, '\n');
                //     std::cout << "������Ч��������һ�����֣�1~126��: ";
                // }
                int id = getRandomInt(126) + 1;
                CapooManager::getInstance().add(new CapooEntity(id, sf::Vector2i(getRandomInt(WINDOW_WIDTH), getRandomInt(WINDOW_HEIGHT))));
            } 
        }

        CapooManager::getInstance().handleInput(event);
            
    }
}

void Game::update(float deltaTime)
{

    CapooManager::getInstance().update(deltaTime);
}

void Game::render()
{
    mainwindow->clear(sf::Color(255, 255, 255, 0));
    CapooManager::getInstance().draw(mainwindow);
    mainwindow->display();
}

void Game::quit()
{

}

void Game::startGame()
{
    lastTime = getAbsolutTime();

    init();

    while (mainwindow->isOpen())
    {
        deltaTime = getAbsolutTime() - lastTime;
        if (deltaTime < 0.008f)
        {
        float sleepTime = 1.0f / FPS - deltaTime;
        sf::sleep(sf::seconds(sleepTime));
        deltaTime = getAbsolutTime() - lastTime;
        }

        lastTime = getAbsolutTime();
        if (deltaTime > 0.05f) deltaTime = 0.05f;

        processInput();
        update(deltaTime);
        render();
    }

    quit();

}

// global function to gain game objection.
Game &game()
{
    return *gameptr;
}

