#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <windows.h>
#include "Structs.h"

using namespace std;

class GameObgect
{
public:
    // показывает комару нужно ли идти
    bool needWalk = false;
    bool isLife = false;
    // настоящие координаты объекта
    int x;
    int y;

    // координаты объекта на прошлом ходу 
    int tmpx=0;
    int tmpy=0;

    // промежуточные координаты объекта
    int tmpValueX = 0;
    int tmpValueY = 0;

    // кол-во сделанных шагов (очки в игре) -1 потому, что при первой отрисовки карты вызывается ф-ция updatePos
    // которая обновляет опложение игрока и увеличивает каунтер ходов
    int stepsCount = -1;
    
    // тело объекта, которое выводиться на экран
    string body;

    // обновление координат объекта
    void updatePos(int x, int y);
    void updatePos();
    // проверка на то, сидит ли лягушка в одной клетке с объектом
    bool getСollision(GameObgect player);
    // проверка на то, пересёкла ли лягушка объект по вертикали или горизонтали
    bool getOverflightСollision(GameObgect player);
    // проверка на то, пересекла ли лягушка объект по диагонали
    bool getDiagonalOverflightСollision(GameObgect player);
    // движение объекта
    void walk(int row, int col, Settings settings);

    void intellectWalk(int row, int col, Settings settings, Highground Highground, GameObgect player);
};
