#pragma once

#include <string>
#include <iostream>
#include "Structs.h"
#include <Windows.h>
#include "GameObgects.h"

using namespace std;

class Map
{
public:
    int row;
    int col;

    void SetSettings(Settings settings);
    void CreateHighground();
    bool HasHighground(int x, int y);
    bool HasMosquito(int x, int y, GameObgect* mosquitoGroup, Settings settings);
    void updateHighgroundMaxCount();

    void createRuneHighground(Settings settings);
    bool isRuneHighground(int x, int y);

    Highground getRandomHighground();
    int getMaxHighground();
	void LoadMap(GameObgect player, GameObgect* mosquitoGroup, Settings settings);
private:
    int highgroundLVL = 4;
    int highgroundMaxCount;
    Highground *highground;
    MapElements mapElements;
};
