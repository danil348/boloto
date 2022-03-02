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
    // создание массива возвышенностей со своими рандомными координатами
    void CreateHighground();
    // возвращает есть ли возвышенность с переданными координатами
    bool HasHighground(int x, int y);
    bool HasMosquito(int x, int y, GameObgect* mosquitoGroup, Settings settings);
    // подсчёт нужного кол-ва возвышенностей, исходя из кол-ва колонок и строк
    void updateHighgroundMaxCount();

    void createRuneHighground(Settings settings);
    bool isRuneHighground(int x, int y);

    // возвращает рандомную возвышенность
    Highground getRandomHighground();
    // возврящает максимальное кол-во возвышенностей 
    int getMaxHighground();
    // рисует карту, лягуху, комара
	void LoadMap(GameObgect player, GameObgect* mosquitoGroup, Settings settings);
private:
    int highgroundLVL = 4;
    int highgroundMaxCount;
    // массив с возвышенностями 
    Highground *highground;
    // элементы карты (стенки, перекрестия и т.д)
    MapElements mapElements;
};
