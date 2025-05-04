#include "Game.h"

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    Game game(hInstance, nCmdShow);
#else
int main() {
    Game game;
#endif

    game.startGame();
    return 0;
}