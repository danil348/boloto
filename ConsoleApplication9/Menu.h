#pragma once
#include "Sound.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include "Structs.h"
#include "GameObgects.h"
#include "DataStorage.h"

#define ESCAPE 27
#define ENTER 13
#define RIGHT 77
#define LEFT 75
#define DOWN 80
#define UP 72

using namespace std;

class Menu
{
public:
	Sound sound;
	Settings settings;

	void init();
	void draw();
	int getkey();
	void update(int menuIndex);
	bool runnig();
	void drawGameRules(int menuIndex);
	void settingsDrow();
	void pumpDrow();
	void ConsoleCursorVisible(bool show);
	void changeRunning(bool value);
	bool isEnd();

private:
	bool isRunning = true;
	bool needUpdate = true;
	bool end = false;

	char cmd;
	int consoleWidth;
	int consoleHeigth;

	int activeMenu = 0;
	static const int firstMenuSize = 6;
	string firstMenu[firstMenuSize] = { "Новая игра", "прокачка", "Настройки", "правила", "сбросить прогресс", "Выход" };

	int activeSetting = 0;
	static const int settingMenuSize = 6;
	string settingName[settingMenuSize] = { "уровень сложности карты", "максимальный шаг комара", 
		"шрифт", "кол-во комаров", "интеллект комара", "музыка"};

	int activePump = 0;
	static const int PumpMenuSize = 5;
	string pumpName[PumpMenuSize] = { "длинна прыжка", "бонус к прыжку от рун", "время действия руны",
		"шанс появления руны", "максимально рун на карте"};

	DataStorage storage;
	MapElements mapElements;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	CONSOLE_CURSOR_INFO structCursorInfo;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 

};

