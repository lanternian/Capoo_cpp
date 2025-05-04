#ifndef GAME_H
#define GAME_H

#ifdef _WIN32
#define UNICODE
#define NOMINMAX
#include <windows.h>
#include "resources.h"

#define TRAY_ICON_ID 1
#define WM_TRAYICON (WM_USER + 1)
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "SpineData.h"
#include "SpineEntity.h"
#include "CapooEntity.h"
#include "ResourceManager.h"
#include "CapooInfo.h"
#include "CapooManager.h"
#include "globalVar.h"

class Game
{
public:
    Game();
    Game(HINSTANCE hInstance, int nCmdShow);
    ~Game();
    bool initWindow();
    float getAbsolutTime();
    void init();
    void startGame();
    void processInput();
    void update(float deltaTime);
    void render();
    void quit();
    
    sf::RenderWindow &getWindow() const{ return *mainwindow; }
private:
    sf::RenderWindow *mainwindow;

    float lastTime;
    float deltaTime;

#ifdef _WIN32
private:
    HINSTANCE hInstance;
    int nCmdShow;
    HWND hwnd;
    HWND subhwnd;
    HICON hIcon;

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void AddTrayIcon();
    void HandleTrayIcon(WPARAM wParam, LPARAM lParam);
#endif

};

Game& game();

#endif
