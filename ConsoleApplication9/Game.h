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
	// ���� ���-�� ����� � �������, �������� �����, �������� �������, �������� ������ 
	void init();
	// ��������� ���� ����, ����� �������� ���� ���������� �� �������.
	void GameEnd(bool isVin, bool mosquitoSuicide);
	// ���������� �������� �������� �� ����
	bool running();
	// �������� �������� �����, ������, ������
	void creatGameObjects();
	// ���������� ���������� fontSize � ����������� �� ������ �������
	void updateFontSize();
	// ������� ����
	void gameRefresh();
	void switchMosquitoState(GameObgect& mosquito);
	void GetConsoleParameters(int& x, int& y);
	// ���� ����� �����������, �������������� ��� �������
	void update();
	// ���������� ���������� ����������� �������
	void refreshUpdate();
	// ��������� ������� ������, ������� ����� �� �� ������
	bool playerUpdate(int x,int y);
	// ������������ ��������� ����� �� ����������
	bool isVerticalSteps(int x, int y, int tmpx, int tmpy);
	// �������� �����
	void ChekOnInt(int& value);
	void Validatuon(int& value, string textError, int case1,int case2);
private:
	// �������� ��������� ���� � ����
	bool gameEnd = false;
	// ��������/��������� ����
	bool isRunning = false;
	// ���������� ����� �� ��������� �������
	bool needUpdate = true;
	// ������� ������� ���� ����
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

	// ��� ��������� �������� ����
	HWND hwnd = GetConsoleWindow();
	LPPOINT mousePoint = (LPPOINT)malloc(sizeof(*mousePoint));

	// ��������� �������
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

	COORD coord;
};
