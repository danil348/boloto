#include "Game.h"

using namespace std;

void Game::init()
{
	updateFontSize();
	storage.getSetting(menu.settings);

	wcscpy_s(fontInfo.FaceName, L"Consolas"); 
	fontInfo.dwFontSize.Y = fontCases.font[menu.settings.fontSizeCount][0];

	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);

	menu.init();

	while (menu.runnig() == true) {
		updateFontSize();
		menu.draw();
		menu.update(0);
	}
	if (menu.isEnd() == true) {
		storage.saveSetting(menu.settings);
		exit(0);
	}
	gameRefresh();
}

void Game::GameEnd(bool isVin, bool mosquitoSuicide)
{
	cheatsSteps = 0;
	player.updatePos();
	timeManager.stopTime();
	
	gameEnd = true;
	needUpdate = false;

	system("cls");

	if (isVin == true && mosquitoSuicide == true) {
		menu.settings.score++;
		cout << "Победа!!!\nКомар совершил суицид...\nКол-во ходов: " << player.stepsCount << endl;
		timeManager.stopTime();
		cout << "Карта: " << row << "x" << col << endl;
	}
	else if (isVin == true) {
		menu.settings.score++;
		cout << "Победа!!!\nЛягушка съела комара\nКол-во ходов: " << player.stepsCount << endl;
		timeManager.stopTime();
		cout << "Карта: " << row << "x" << col << endl;
	}
	else {
		if (menu.settings.score > 0) {
			menu.settings.score--;
		}
		timeManager.stopTime();
		menu.sound.playSoundEffect(1);
		cout << "Вы не справились с управлением и лягушка утонула...\nКол-во ходов " << player.stepsCount << endl;
	}
	cout << "\nнажмите Enter, чтобы продолжить";

	while (_kbhit()) { 
		_getch();
	}

	do
	{
		key = _getch();
		Sleep(50);
		if (key == -32) key = _getch();
		switch (key)
		{
		case 13:
			Sleep(100);
			menu.changeRunning(1);
			while (menu.runnig()) {
				updateFontSize();
				menu.draw();
				menu.update(0);
			}
			if (menu.getkey() == 0 && menu.isEnd() == false) {
				gameRefresh();
				update();
			}

			if (menu.isEnd() == true) {
				storage.saveSetting(menu.settings);
				exit(0);
			}
			break;
		case 27:
			storage.saveSetting(menu.settings);
			exit(0);
			break;
		default: break;
		}
	} while (key != 27 && key != 13);

	key = 0;
}

void Game::update()
{
	if (needUpdate == true) {
		system("cls");
		map.LoadMap(player, mosquitoGroup, menu.settings);
	}
	needUpdate = false;
}

bool Game::running()
{
	return isRunning;
}

void Game::creatGameObjects()
{
	mosquitoGroup = new GameObgect[menu.settings.mosquitoCount];
	menu.settings.mosquitoCountLife = menu.settings.mosquitoCount;

	
	for (int i = 0; i < menu.settings.mosquitoCount; i++) {
		mosquitoGroup[i].needWalk = true;
		mosquitoGroup[i].isLife = true;
		mosquitoGroup[i].updatePos(rand() % col, rand() % row);
		mosquitoGroup[i].body = "===";
	}

	map.col = col;
	map.row = row;
	map.CreateHighground();

	highground = map.getRandomHighground();

	player.tmpx = highground.x;
	player.tmpy = highground.y;
	player.updatePos(highground.x, highground.y);
	player.body = "kva";
	player.stepsCount = 0;
}

void Game::updateFontSize()
{
	int x;
	int y; 
	RECT rc;
	fontInfo.dwFontSize.Y = menu.settings.fontSize[menu.settings.fontSizeCount][0];

	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	HWND hWnd = GetConsoleWindow();
	
	GetClientRect(hWnd, &rc);
	GetConsoleParameters(x, y);

	menu.settings.maxRow = rc.bottom / fontCases.font[menu.settings.fontSizeCount][4] - 8;
	menu.settings.maxCol = rc.right / fontCases.font[menu.settings.fontSizeCount][3] - 4;

	if ((menu.settings.maxRow > (y - 8) || menu.settings.maxCol > (x - 2) / 3 - 1)) {
		menu.settings.maxRow = (y - 8);
		menu.settings.maxCol = (x - 2) / 3 - 1;
		if (menu.settings.fontSize[menu.settings.fontSizeCount][0] == 20) {
			menu.settings.maxCol-=2;
		}
		else if (menu.settings.fontSize[menu.settings.fontSizeCount][0] == 18) {
			menu.settings.maxCol -= 4;
		}
		else if (menu.settings.fontSize[menu.settings.fontSizeCount][0] == 16) {
			menu.settings.maxCol -= 5;
		}
	}
}

void Game::GetConsoleParameters(int& x, int& y)
{
	if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
		x = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
		y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	}
}

void Game::gameRefresh()
{
	gameEnd = false;
	needUpdate = true;

	updateFontSize();

	map.SetSettings(menu.settings);

	cout << "введите количество клеток по вертикали ";
	Validatuon(row, "введённое значение должно быть больше 5 и меньше или равно ", menu.settings.minRow, menu.settings.maxRow);

	cout << "введите количество клеток по горизонтали ";
	Validatuon(col, "введённое значение должно быть больше 5 и меньше или равно ", menu.settings.minCol, menu.settings.maxCol);

	creatGameObjects();

	isRunning = true;
	
	timeManager.startTime();
}

void Game::switchMosquitoState(GameObgect& mosquito)
{
	if (mosquito.getСollision(player) == true && mosquito.isLife == true) {
		menu.settings.mosquitoCountLife--;
		mosquito.needWalk = false;
		mosquito.isLife = false;
	}
}


void Game::refreshUpdate()
{
	updateFontSize();
	if ((GetKeyState(VK_RBUTTON) & 0x8000) && gameEnd == false) {
		needUpdate = true;

		GetCursorPos(mousePoint);
		ScreenToClient(hwnd, mousePoint);
		
		// ход игрока
		needUpdate = playerUpdate(mousePoint[0].x, mousePoint[0].y);
		for (int i = 0; i < menu.settings.mosquitoCount; i++) {
			mosquitoGroup[i].needWalk = needUpdate;
		}

		// ход объекта
		// проверка на то, наступил ли игрок на объект
		bool flag = false;
		for (int i = 0; i < menu.settings.mosquitoCount; i++) {
			if (mosquitoGroup[i].getСollision(player) == true && mosquitoGroup[i].isLife == true) {
				menu.settings.mosquitoCountLife--;
				mosquitoGroup[i].needWalk = false;
				mosquitoGroup[i].isLife = false;
			}
			if (menu.settings.mosquitoCountLife == 0) {
				flag = true;
			}
		}

		if (flag == false) {
			for (int i = 0; i < menu.settings.mosquitoCount; i++) {
				if (mosquitoGroup[i].needWalk == true) {
					if (menu.settings.mosquitoIntellect == true) {
						mosquitoGroup[i].intellectWalk(row, col, menu.settings, highground, player);
					}
					else {
						mosquitoGroup[i].walk(row, col, menu.settings);
					}
					
					// проверка на то, наступил ли объект на игрока
					int _flag = false;
					if (mosquitoGroup[i].getСollision(player) == true && mosquitoGroup[i].isLife == true) {
						menu.settings.mosquitoCountLife--;
						mosquitoGroup[i].isLife = false;
						mosquitoGroup[i].needWalk = false;
					}
					if (menu.settings.mosquitoCountLife == 0) {
						GameEnd(true, true);
					}
				}
			}
		}
		else {
			GameEnd(true, false);
		}
	}
	else {
		needUpdate = false;
	}
}

bool Game::playerUpdate(int x, int y)
{

	player.tmpx = (x - fontCases.font[menu.settings.fontSizeCount][1]) / fontCases.font[menu.settings.fontSizeCount][3];
	player.tmpy = (y - fontCases.font[menu.settings.fontSizeCount][2]) / fontCases.font[menu.settings.fontSizeCount][4];
	cheatsSteps += (player.tmpx == player.x && player.tmpy == player.y && cheatsSteps < minCheatsSteps);

	// елси игрок нажал на облость поля игры
	if (x >= fontCases.font[menu.settings.fontSizeCount][1] && y >= fontCases.font[menu.settings.fontSizeCount][2] &&
		(x - fontCases.font[menu.settings.fontSizeCount][1]) / fontCases.font[menu.settings.fontSizeCount][3] < col &&
		(y - fontCases.font[menu.settings.fontSizeCount][2]) / fontCases.font[menu.settings.fontSizeCount][4] < row) {
		// если в той ячейке, куда нажал игрок есть возвышенность
		if (map.HasHighground(player.tmpy, player.tmpx) == true) {
			// если возвышенность находится не больше, чем в пяти клетках от игрока
			if (abs(player.x - player.tmpx) <= menu.settings.playerCurrentStep && abs(player.y - player.tmpy) <= menu.settings.playerCurrentStep) {
				// если игрок ходит влево, вправо, вверх, вниз
				if ((player.x != player.tmpx && player.y == player.tmpy) || 
					(player.y != player.tmpy && player.x == player.tmpx)) {
					for (int i = 0; i < menu.settings.mosquitoCount; i++) {
						if (mosquitoGroup[i].getOverflightСollision(player) && mosquitoGroup[i].isLife == true) {
							menu.settings.mosquitoCountLife--;
							mosquitoGroup[i].isLife = false;
							mosquitoGroup[i].needWalk = false;
						}
					}
					if (menu.settings.mosquitoCountLife == 0) {
						GameEnd(true, false);
					}
					player.updatePos();

					// реализация рун
					if (menu.settings.currentRuneState == 1 && menu.settings.runeIsActive == true) {
						menu.settings.playerCurrentStep -= menu.settings.runeBoost * menu.settings.currentRuneCount;
						menu.settings.currentRuneCount = 0;
						menu.settings.runeIsActive = false;
					}
					else if (menu.settings.currentRuneState > 0) {
						menu.settings.currentRuneState--;
					}
					else {
						menu.settings.runeIsActive = false;
					}
					if (map.isRuneHighground(player.tmpy, player.tmpx) == true) {
						menu.settings.currentRuneCount++;
						menu.settings.currentRuneState = menu.settings.runeLvl;
						menu.settings.runeIsActive = true;
						menu.settings.playerCurrentStep += menu.settings.runeBoost;
					}
					menu.sound.playSoundEffect(2);
					return true;
				}
				// если игрок ходит по вертикали
				else if (isVerticalSteps(player.x, player.y, player.tmpx, player.tmpy)) {
					for (int i = 0; i < menu.settings.mosquitoCount; i++) {
						// если игрок перелетел объект по диагонали
						if (mosquitoGroup[i].getDiagonalOverflightСollision(player) && mosquitoGroup[i].isLife == true) {
							menu.settings.mosquitoCountLife--;
							mosquitoGroup[i].isLife = false;
							mosquitoGroup[i].needWalk = false;
						}
					}
					if (menu.settings.mosquitoCountLife == 0) {
						GameEnd(true, false);
					}
					player.updatePos();

					// реализация рун
					if (menu.settings.currentRuneState == 1 && menu.settings.runeIsActive == true) {
						menu.settings.playerCurrentStep -= menu.settings.runeBoost * menu.settings.currentRuneCount;
						menu.settings.currentRuneCount = 0;
						menu.settings.runeIsActive = false;
					}
					else if (menu.settings.currentRuneState > 0) {
						menu.settings.currentRuneState--;
					}
					else {
						menu.settings.runeIsActive = false;
					}
					if (map.isRuneHighground(player.tmpy, player.tmpx) == true) {
						menu.settings.currentRuneCount++;
						menu.settings.currentRuneState = menu.settings.runeLvl;
						menu.settings.runeIsActive = true;
						menu.settings.playerCurrentStep += menu.settings.runeBoost;
					}
					menu.sound.playSoundEffect(2);
					return true;
				}
			}
		}
		else {
			if (cheatsSteps != minCheatsSteps) {
				GameEnd(false, false);
			}
		}
	}
	return false;
}

bool Game::isVerticalSteps(int x, int y, int tmpx, int tmpy)
{
	for (int i = 0; i <= menu.settings.playerCurrentStep; i++) {
		if ((x + i == tmpx && y + i == tmpy) ||
			(x - i == tmpx && y - i == tmpy) ||
			(x + i == tmpx && y - i == tmpy) ||
			(x - i == tmpx && y + i == tmpy)) {
			return true;
		}
	}
	return false;
}

void Game::ChekOnInt(int& value)
{
	while (true) {
		if (scanf_s("%d", &value) == false || getchar() != '\n') {
			while (getchar() != '\n');
			cout << "Неверный ввод ";
		}
		else {
			break;
		}
	}
}

void Game::Validatuon(int& value, string textError, int case1,int case2)
{
	do
	{
		ChekOnInt(value);
		if (value < case1 || value > case2) {
			printf("%s%d\n", textError.c_str(), case2);
		}
	} while (value < case1 || value > case2);
}