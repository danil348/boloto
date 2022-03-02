#include "Menu.h"


void Menu::init() { 
	system("cls");
	SetConsoleTitle(L"Болото");
	ConsoleCursorVisible(false);
	sound.addSoundEffect("switch.wav");
	sound.addSoundEffect("water.wav");
	sound.addSoundEffect("slap.wav");
}

void Menu::draw()
{
	system("cls");
	if (needUpdate == true) {
		for (int i = 0; i < firstMenuSize; i++)
		{
			cout << firstMenu[i];
			for (int j = firstMenu[i].size(); j < 15; j++) {
				cout << " ";
			}
			if (activeMenu == i) {
				cout << "\t<--";
			}
			cout << endl;
		}
	}
}



int Menu::getkey()
{
	return activeMenu;
}

void Menu::update(int menuIndex)
{
	if (menuIndex == 0) {

		cmd = _getch();

		if (cmd == -32) cmd = _getch();
		switch (cmd)
		{
		case ESCAPE:
			end = true;
			isRunning = false;
			break;
		case ENTER:
			sound.playSoundEffect(0);
			if (activeMenu == 0) {
				isRunning = false;
				system("cls");
			}
			else if (activeMenu == 1) {
				update(2);
			}
			else if (activeMenu == 2) {
				update(3);
			}
			else if (activeMenu == 3) {
				update(1);
			}
			else if (activeMenu == 4) {
				update(4);
			}
			else if (activeMenu == 5) {
				end = true;
				isRunning = false;
			}
			break;
		case UP:
			sound.playSoundEffect(0);
			if (activeMenu > 0) {
				activeMenu--;
			}
			else {
				activeMenu = firstMenuSize - 1;
			}
			break;
		case DOWN:
			sound.playSoundEffect(0);
			if (activeMenu < firstMenuSize - 1) {
				activeMenu++;
			}
			else {
				activeMenu = 0;
			}
			break;
		default: break;
		}
	}
	else if (menuIndex == 1) {
		do {
			drawGameRules(1);

			cmd = _getch();

			if (cmd == -32) cmd = _getch();
			switch (cmd) {
			case ESCAPE: system("cls"); sound.playSoundEffect(0); break;
			case ENTER: system("cls"); sound.playSoundEffect(0); break;
			default: break;
			}
		} while (cmd != ESCAPE && cmd != ENTER);
	}
	else if (menuIndex == 2) {

		do {
			pumpDrow();
			
			cmd = _getch();

			if (cmd == -32) cmd = _getch();
			switch (cmd) {
			case ESCAPE: system("cls"); activePump = 0; sound.playSoundEffect(0); break;
			case ENTER: system("cls"); activePump = 0; sound.playSoundEffect(0); break;
			case UP:
				sound.playSoundEffect(0);
				if (activePump > 0) {
					activePump--;
				}
				else {
					activePump = PumpMenuSize - 1;
				}
				break;
			case DOWN:
				sound.playSoundEffect(0);
				if (activePump < PumpMenuSize - 1) {
					activePump++;
				}
				else {
					activePump = 0;
				}
				break;
			case LEFT:
				sound.playSoundEffect(0);
				if (activePump == 0) {
					if (settings.playerCurrentStep >= 2) {
						settings.playerCurrentStep--;
						settings.score++;
					}
				}
				else if (activePump == 1) {
					if (settings.runeBoost >= 2) {
						settings.runeBoost--;
						settings.score++;
					}
				}
				else if (activePump == 2) {
					if (settings.runeLvl >= 2) {
						settings.runeLvl--;
						settings.score++;
					}
				}
				else if (activePump == 3) {
					if (settings.chanceToCreateRune >= 2) {
						settings.chanceToCreateRune--;
						settings.score++;
					}
				}
				else if (activePump == 4) {
					if (settings.runeCount >= 2) {
						settings.runeCount--;
						settings.score++;
					}
				}
				break;
			case RIGHT:
				sound.playSoundEffect(0);
				if (activePump == 0 && settings.score > 0) {
					if (settings.playerCurrentStep < settings.maxPlayerMaxStep) {
						settings.playerCurrentStep++;
						settings.score--;
					}
				}
				else if (activePump == 1 && settings.score > 0) {
					if (settings.runeBoost < settings.maxRuneBoost) {
						settings.runeBoost++;
						settings.score--;
					}
				}
				else if (activePump == 2 && settings.score > 0) {
					if (settings.runeLvl < settings.maxRuneLvl) {
						settings.runeLvl++;
						settings.score--;
					}
				}
				else if (activePump == 3 && settings.score > 0) {
					if (settings.chanceToCreateRune < settings.maxChanceToCreateRune) {
						settings.chanceToCreateRune++;
						settings.score--;
					}
				}
				else if (activePump == 4 && settings.score > 0) {
					if (settings.runeCount < settings.maxRuneCount) {
						settings.runeCount++;
						settings.score--;
					}
				}
				break;
			default: break;
			}
		} while (cmd != ESCAPE && cmd != ENTER);
	}
	else if (menuIndex == 3) {
		do {
			settingsDrow();

			cmd = _getch();

			if (cmd == -32) cmd = _getch();
			switch (cmd) {
			case ESCAPE: system("cls"); activeSetting = 0; sound.playSoundEffect(0); break;
			case ENTER: system("cls"); activeSetting = 0; sound.playSoundEffect(0); break;
			case UP:
				sound.playSoundEffect(0);
				if (activeSetting > 0) {
					activeSetting--;
				}
				else {
					activeSetting = settingMenuSize - 1;
				}
				break;
			case DOWN:
				sound.playSoundEffect(0);
				if (activeSetting < settingMenuSize - 1) {
					activeSetting++;
				}
				else {
					activeSetting = 0;
				}
				break;
			case LEFT:
				sound.playSoundEffect(0);
				if (activeSetting == 0) {
					if (settings.highgroundLVL >= 2) {
						settings.highgroundLVL--;
					}
				}
				else if (activeSetting == 1) {
					if (settings.mosquitoCurrentStep >= 2) {
						settings.mosquitoCurrentStep--;
					}
				}
				else if (activeSetting == 2) {
					if (settings.fontSizeCount > 0) {
						settings.fontSizeCount--;
						settings.currentFontSize = settings.fontSize[settings.fontSizeCount][0];
					}
				}
				else if (activeSetting == 3) {
					if (settings.mosquitoCount > 1) {
						settings.mosquitoCount--;
					}
				}
				else if (activeSetting == 4) {
					settings.mosquitoIntellect = !settings.mosquitoIntellect;
				}
				else if (activeSetting == 5) {
					sound.isActive = !sound.isActive;
				}
				break;

			case RIGHT:
				sound.playSoundEffect(0);
				if (activeSetting == 0) {
					if (settings.highgroundLVL < settings.maxHighgroundLVL) {
						settings.highgroundLVL++;
					}
				}
				else if (activeSetting == 1) {
					if (settings.mosquitoCurrentStep < settings.maxMosquitoMaxStep) {
						settings.mosquitoCurrentStep++;
					}
				}
				else if (activeSetting == 2) {
					if (settings.fontSizeCount < settings.fonts) {
						settings.fontSizeCount++;
						settings.currentFontSize = settings.fontSize[settings.fontSizeCount][0];
					}
				}
				else if (activeSetting == 3) {
					if (settings.mosquitoCount < settings.maxMosquitoCount) {
						settings.mosquitoCount++;
					}
				}
				else if (activeSetting == 4) {
					settings.mosquitoIntellect = !settings.mosquitoIntellect;
				}
				else if (activeSetting == 5) {
					sound.isActive = !sound.isActive;
				}
				break;
			default: break;
			}
		} while (cmd != ESCAPE && cmd != ENTER);
	}
	else if (menuIndex == 4) {
		do {
			system("cls");
			cout << "Вы точно хотите сбросить игру до дефолтного состояния?\nПосле подтверждения ваш игровой прогресс будет потерян\n\n";
			cout << "Нажмите Enter, чтобы подтвердить\nНажмите Esc, чтобы отметь и выйти в главное меню\n";

			cmd = _getch();

			if (cmd == -32) cmd = _getch();
			switch (cmd) {
			case ESCAPE: system("cls"); sound.playSoundEffect(0); break;
			case ENTER: storage.refreshSetting(settings); sound.playSoundEffect(0); break;
			default: break;
			}
		} while (cmd != ESCAPE && cmd != ENTER);
	}
}

bool Menu::runnig()
{
	return isRunning;
}

void Menu::drawGameRules(int menuIndex)
{
	system("cls");

	if (menuIndex == 1) {
		cout << "Перед началом игры, игрок выбирает размеры поля. Он вводит их вручную\n";
		cout << "После ввода размеров поля перед игроком появляется карта\n";
		cout << "Игра заканчивается, когда лягушка съест всех комаров,\nили игрок отправит лягушку на поле с водой\n";

		cout << "===";
		cout << "  -  комар\n\n";

		cout << "kva";
		cout << "  -  комар\n\n";

		SetConsoleTextAttribute(hStdOut, (WORD)((9 << 4) | 14));
		cout << "   ";
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 7));
		cout << "  -  вода\n\n";

		SetConsoleTextAttribute(hStdOut, (WORD)((10 << 4) | 14));
		cout << "   ";
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 7));
		cout << "  -  горка\n\n";

		SetConsoleTextAttribute(hStdOut, (WORD)((10 << 4) | 14));
		cout << "\x1b[31m===\x1b[0m";
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 7));
		cout << "  -  горка с комаром\n\n";

		SetConsoleTextAttribute(hStdOut, (WORD)((10 << 4) | 14));
		SetConsoleOutputCP(437);
		cout << "\x1b[31m==" << mapElements.Elements[13] << "\x1b[0m";
		SetConsoleOutputCP(1251);
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 7));
		cout << "  -  горка с комаром и руной\n\n";

		cout << endl << "Нажмите Enter, чтобы продолжить";
	}
}

void Menu::settingsDrow()
{
	system("cls");

	for (int i = 0; i < settingMenuSize; i++)
	{
		cout << settingName[i];
		if (i == 0) {
			cout << "\t\t" << settings.highgroundLVL << "/" << settings.maxHighgroundLVL;
		}
		else if (i == 1) {
			cout << "\t\t" << settings.mosquitoCurrentStep << "/" << settings.maxMosquitoMaxStep;
		}
		else if (i == 2) {
			cout << "\t\t\t\t" << settings.fontSize[settings.fontSizeCount][0];
		}
		else if (i == 3) {
			cout << "\t\t\t" << settings.mosquitoCount << "/" << settings.maxMosquitoCount;
		}
		else if (i == 4) {
			if (settings.mosquitoIntellect == true) {
				cout << "\t\tвкл\t";
			}
			else {
				cout << "\t\tвыкл\t";
			}
		}
		else if (i == 5) {
			if (sound.isActive == true) {
				cout << "\t\t\t\tвкл\t";
			}
			else {
				cout << "\t\t\t\tвыкл\t";
			}
		}
		if (activeSetting == i) {
			cout << "\t<--";
		}
		cout << endl;
	}

	cout << endl << "Нажмите Enter, чтобы применить и продолжить";
}

void Menu::pumpDrow()
{
	system("cls");
	cout << "Очки прокачки: " << settings.score << endl << endl;
	for (int i = 0; i < PumpMenuSize; i++)
	{
		cout << pumpName[i];
		if (i == 0) {
			cout << "\t\t\t" << settings.playerCurrentStep << "/" << settings.maxPlayerMaxStep;
		}
		else if (i == 1) {
			cout << "\t\t" << settings.runeBoost << "/" << settings.maxRuneBoost;
		}
		else if (i == 2) {
			cout << "\t\t" << settings.runeLvl << "/" << settings.maxRuneLvl;
		}
		else if (i == 3) {
			cout << "\t\t" << settings.chanceToCreateRune << "%/" << settings.maxChanceToCreateRune << "%";
		}
		else if (i == 4) {
			cout << "\t" << settings.runeCount << "/" << settings.maxRuneCount;
		}

		if (activePump == i) {
			cout << "\t<--";
		}
		cout << endl;
	}
	cout << endl << "Нажмите Enter, чтобы применить и продолжить";
}

void Menu::ConsoleCursorVisible(bool show)
{
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; 
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void Menu::changeRunning(bool value)
{
	isRunning = value;
}

bool Menu::isEnd()
{
	return end;
} 