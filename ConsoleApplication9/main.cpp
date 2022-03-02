#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include "Game.h"

using namespace std;

int SDL_main(int argc, char* argv[])
{
    //SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0)); 

    Game game;

    game.init();

    while (game.running())
    {
        // отрисовка карты, персножей, интерфейса
        game.update();

        // задержка для предотвращения повторного нажатия
        Sleep(50);

        // проверка действий игрока, которые включают отрисовку (update)
        game.refreshUpdate();
    }
    return 0;
}