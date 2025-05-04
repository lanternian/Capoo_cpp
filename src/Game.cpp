#include "Game.h"

#ifdef DEBUG
#include <spine/Debug.h>
spine::DebugExtension dbgExtension(spine::SpineExtension::getInstance());
#endif

void TransparentWindow(sf::RenderWindow *window) {
    // transparent window
    HWND hWnd = window->getSystemHandle();
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hWnd, RGB(BG_R, BG_G, BG_B), 0, LWA_COLORKEY);
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
#ifdef DEBUG
    spine::SpineExtension::setInstance(&dbgExtension);
#endif
}

Game::Game(HINSTANCE hInstance, int nCmdShow)
        : hInstance(hInstance), nCmdShow(nCmdShow), hwnd(NULL), subhwnd(NULL) 
{
    srand(time(NULL));
    gameptr = this;
#ifdef DEBUG
    spine::SpineExtension::setInstance(&dbgExtension);
#endif  
}

Game::~Game()
{


#ifdef DEBUG
    dbgExtension.reportLeaks();
#endif 
}

bool Game::initWindow()
{
#ifdef _WIN32
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = StaticWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Load icon
    hIcon = (HICON)LoadImage(
        NULL,
        L"data/images/capoo.ico",
        IMAGE_ICON,
        64, 64,
        LR_LOADFROMFILE
    );

    if (hIcon == NULL) {
        // Load icon failed, output error
        DWORD error = GetLastError();
        MessageBox(NULL, TEXT("Failed to load icon!"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return false;
    } else {
        wc.hIcon = hIcon;
    }

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Main Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        this // Pass "this" pointer to WM_CREATE message
    );

    if (hwnd == NULL) {
        return false;
    }

    // Create sub window
    subhwnd = CreateWindowEx(
        WS_EX_LAYERED,
        CLASS_NAME,
        L"Sub Window",
        WS_POPUP,
        0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    if (subhwnd == NULL) {
        return false;
    }
    // SetLayeredWindowAttributes(subhwnd, 0, 0, LWA_ALPHA);
    SetLayeredWindowAttributes(subhwnd, RGB(BG_R, BG_G, BG_B), 0, LWA_COLORKEY);
    SetWindowPos(subhwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    ShowWindow(subhwnd, nCmdShow);
    AddTrayIcon();

    mainwindow = new sf::RenderWindow(subhwnd);
    if (!mainwindow) return false;
    return true;
#else
    mainwindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT-10), "Spine SFML - capoo", sf::Style::None);
    if (mainwindow!=nullptr) {
        mainwindow->setPosition(sf::Vector2i(0,0));
        TransparentWindow(mainwindow);
        return true;
    }
    else
        return false;
#endif
}

float Game::getAbsolutTime()
{
    static sf::Clock clock;
    return clock.getElapsedTime().asSeconds();
}

void Game::init()
{
    if (!initWindow()) 
        exit(-1);
    CapooEntity *a = new CapooEntity(1, sf::Mouse::getPosition(game().getWindow()));
    CapooManager::getInstance().add(a);
}

void Game::processInput()
{
    static sf::Event event;
    while (mainwindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mainwindow->close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Q) {
                mainwindow->close();
            }
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
    mainwindow->clear(sf::Color(BG_R, BG_G, BG_B ,0));
    CapooManager::getInstance().draw(mainwindow);
    mainwindow->display();
}

void Game::quit()
{
    CapooManager::getInstance().clear();
    delete mainwindow;

}

void Game::startGame()
{
    lastTime = getAbsolutTime();

    init();
#ifdef _WIN32
    MSG msg = {};
#endif
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
        
#ifdef _WIN32
        // Handle Windows messages
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                mainwindow->close();
            }
        }
#endif
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

#ifdef _WIN32
void Game::AddTrayIcon() {
    // Add tray icon
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = TRAY_ICON_ID;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = hIcon;  // Use loaded icon
    lstrcpy(nid.szTip, L"Sample Tray Icon");

    Shell_NotifyIcon(NIM_ADD, &nid);
}



LRESULT CALLBACK Game::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_TRAYICON:
        HandleTrayIcon(wParam, lParam);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1001) {  // Exit menu item ID
            PostQuitMessage(0);
        }
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK Game::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CREATE) {
        // Retrieve Game instance from lpCreateParams
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        Game* pThis = (Game*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        return pThis->WindowProc(hwnd, uMsg, wParam, lParam);
    }

    // Get the Game instance
    Game* pThis = (Game*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (pThis) {
        return pThis->WindowProc(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Game::HandleTrayIcon(WPARAM wParam, LPARAM lParam) {
    if (lParam == WM_RBUTTONDOWN) {
        // Show context menu
        HMENU hMenu = CreatePopupMenu();
        AppendMenu(hMenu, MF_STRING, 1001, L"Exit");

        POINT pt;
        GetCursorPos(&pt);
        SetForegroundWindow(hwnd);
        TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);

        DestroyMenu(hMenu);
    } else if (lParam == WM_LBUTTONDOWN) {
        // Handle left button click
    }
}
#endif