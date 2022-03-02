#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include "Game.h"

using namespace std;

int SDL_main(int argc, char* argv[])
{
    SetConsoleOutputCP(1251);
    srand(time(0)); 

    Game game;

    game.init();

    while (game.running())
    {
        game.update();
        Sleep(50);
        game.refreshUpdate();
    }
    return 0;
}