#pragma once
#include "Map.h"
#include "Menu.h"
#include <string>
#include "Sound.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include "Structs.h"
#include "GameObgects.h"
#include "TimeManager.h"
#include "DataStorage.h"

using namespace std;

class Game
{
public:
	// ввод кол-ва строк и колонок, создание карты, создание лягушки, создание комара 
	void init();
	// последний кадр игры, после которого поле становится не активно.
	void GameEnd(bool isVin, bool mosquitoSuicide);
	// возвращает значение запущена ли игра
	bool running();
	// создание сущности карты, комара, лягухи
	void creatGameObjects();
	// обновление переменной fontSize в зависимости от шрифта консоли
	void updateFontSize();
	// рестарт игры
	void gameRefresh();
	void switchMosquitoState(GameObgect& mosquito);
	void GetConsoleParameters(int& x, int& y);
	// если нужна перерисовка, перерисовывает всю консоль
	void update();
	// обновление параметров перерисовки консоли
	void refreshUpdate();
	// обновляет позицию игрока, считает убили ли мы комара
	bool playerUpdate(int x,int y);
	// высчитывание возможных путей по диагоналям
	bool isVerticalSteps(int x, int y, int tmpx, int tmpy);
	// проверка ввода
	void ChekOnInt(int& value);
	void Validatuon(int& value, string textError, int case1,int case2);
private:
	// включает последний кадр в игре
	bool gameEnd = false;
	// включает/выключает игру
	bool isRunning = false;
	// показывает нужно ли обновлять консоль
	bool needUpdate = true;
	// текущие размеры поля игры
	int row;
	int col;

	int cheatsSteps = 0;
	int minCheatsSteps = 5;

	char key = 0;

	Map map;
	GameObgect player;
	MapElements mapElements;
	GameObgect* mosquitoGroup;
	Menu menu;
	DataStorage storage;
	FontCases fontCases;
	Highground highground;
	TimeManager timeManager;

	string playerName;

	// для обработки движения мыши
	HWND hwnd = GetConsoleWindow();
	LPPOINT mousePoint = (LPPOINT)malloc(sizeof(*mousePoint));

	// Получение консоли
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

	COORD coord;
};
