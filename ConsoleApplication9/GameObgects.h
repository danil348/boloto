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
    bool needWalk = false;
    bool isLife = false;
    int x;
    int y;

    int tmpx=0;
    int tmpy=0;

    int tmpValueX = 0;
    int tmpValueY = 0;

    int stepsCount = -1;
    
    string body;

    void updatePos(int x, int y);
    void updatePos();
    bool get—ollision(GameObgect player);
    bool getOverflight—ollision(GameObgect player);
    bool getDiagonalOverflight—ollision(GameObgect player);
    void walk(int row, int col, Settings settings);
    void intellectWalk(int row, int col, Settings settings, Highground Highground, GameObgect player);
};
