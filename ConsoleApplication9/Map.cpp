#include "Map.h"

using namespace std;

void Map::SetSettings(Settings settings)
{
    highgroundLVL = settings.highgroundLVL;
}

void Map::CreateHighground()
{
    updateHighgroundMaxCount();
    highground = new Highground[highgroundMaxCount];
    for (int i = 0; i < highgroundMaxCount; i++) {
        highground[i].x = rand() % col;
        highground[i].y = rand() % row;
    }
}

bool Map::HasHighground(int i, int j)
{
    bool has = false;
    for (int q = 0; q < highgroundMaxCount; q++) {
        if (i == highground[q].y && j == highground[q].x) {
            has = true;
        }
    }
    return has;
}

bool Map::HasMosquito(int x, int y, GameObgect* mosquitoGroup, Settings settings)
{
    for (int i = 0; i < settings.mosquitoCount; i++) {
        if (mosquitoGroup[i].y == x && mosquitoGroup[i].x == y && y < col && mosquitoGroup[i].isLife == true) {
            return 1;
        }
    }
    return false;
}

void Map::updateHighgroundMaxCount()
{
    highgroundMaxCount = row * col / highgroundLVL;
}

void Map::createRuneHighground(Settings settings)
{
    for (int i = 0; i < highgroundMaxCount; i++) {
        highground[i].hasRune = false;
    }

    for (int j = 0; j < settings.runeCount; j++) {
        bool flag = ((rand() % 100) < settings.chanceToCreateRune);
        int runeHG = rand() % highgroundMaxCount;

        for (int i = 0; i < highgroundMaxCount; i++) {
            if (i == runeHG && flag == true) {
                highground[i].hasRune = true;
            }
        }
    }
}

bool Map::isRuneHighground(int i, int j)
{
    bool has = false;
    for (int q = 0; q < highgroundMaxCount; q++) {
        if (highground[q].hasRune == true && i == highground[q].y && j == highground[q].x) {
            has = true;
        }
    }
    return has;
}

Highground Map::getRandomHighground()
{
    return highground[rand() % highgroundMaxCount];
}


int Map::getMaxHighground()
{
    return highgroundMaxCount;
}
void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //ѕолучаем дескриптор вывода на консоль
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));  //”станавливаем атрибуты текста
}
void Map::LoadMap(GameObgect player, GameObgect* mosquitoGroup, Settings settings)
{
    createRuneHighground(settings);

    SetConsoleOutputCP(437);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 && j == 0) {
                cout << mapElements.Elements[9] << mapElements.Elements[5]  << mapElements.Elements[5];
            }
            else if (i == 0 && j != 0 && j != col) {
                cout << mapElements.Elements[5] << mapElements.Elements[5]  << mapElements.Elements[5];
            }
            if (i == 0 && j == col - 1) {
                cout << mapElements.Elements[5] << mapElements.Elements[0];
                cout << endl;
            }
        }
        for (int j = 0; j < col; j++) {
            if (player.y == i && player.x == j && j < col) {
                if (j == 0) {
                    cout << mapElements.Elements[10];
                }
                SetColor(14, 10);
                cout << "\x1b[35m" << player.body.c_str() << "\x1b[0m";
                SetColor(7, 0);
            }
            else if (HasMosquito(i, j, mosquitoGroup, settings) == true && HasHighground(i, j) == true && isRuneHighground(i, j) == true) {
                if (j == 0) {
                    cout << mapElements.Elements[10];
                }
                SetColor(14, 10);
                cout << "\x1b[31m" << mosquitoGroup[0].body[0] << mosquitoGroup[0].body[0] << mapElements.Elements[13] << "\x1b[0m";
                SetColor(14, 10);
                SetColor(7, 0);
            }
            else if (HasMosquito(i, j, mosquitoGroup, settings) == true && HasHighground(i, j) == true) {
                if (j == 0) {
                    cout << mapElements.Elements[10];
                }
                SetColor(14, 10);
                cout << "\x1b[31m" << mosquitoGroup[0].body.c_str() << "\x1b[0m";
                SetColor(14, 10);
                SetColor(7, 0);
            }
            else if (HasMosquito(i,j, mosquitoGroup, settings) == true) {
                if (j == 0) {
                    cout << mapElements.Elements[10];
                }
                SetColor(14, 9);
                cout << "\x1b[31m" << mosquitoGroup[0].body.c_str() << "\x1b[0m";
                SetColor(14, 9);
                SetColor(7, 0);
            }
            else {
                if (HasHighground(i, j) == true && isRuneHighground(i, j) == true) {
                    if (j == 0) {
                        cout << mapElements.Elements[10];
                    }
                    SetColor(14, 10);
                    cout << " " << "\x1b[31m" << mapElements.Elements[13] << "\x1b[0m";
                    SetColor(14, 10); 
                    cout << " ";
                    SetColor(7, 0);
                }
                else if (HasHighground(i, j) == true) {
                    if (j == 0) {
                        cout << mapElements.Elements[10];
                    }
                    SetColor(14, 10);
                    cout << "   ";
                    SetColor(7, 0);
                }
                else {
                    if (j == 0) {
                        cout << mapElements.Elements[10];
                    }
                    SetColor(14, 9);
                    cout << "   ";
                    SetColor(7,0);
                }
            }
            if (j == col - 1) {
                cout << mapElements.Elements[10];
            }
        }
        cout << endl;
        if (i == row - 1) {
            for (int j = 0; j < col; j++) {
                if (j == 0) {
                    cout << mapElements.Elements[1] << mapElements.Elements[5] << mapElements.Elements[5];
                }
                else if (j > 0 && j < col) {
                    cout << mapElements.Elements[5] << mapElements.Elements[5] << mapElements.Elements[5];
                }
            }
            cout << mapElements.Elements[5] << mapElements.Elements[8] << endl;
        }
    }
    SetConsoleOutputCP(1251);
    
    cout << endl;
    cout << "длина шага: " << settings.playerCurrentStep << endl;
    if (settings.runeIsActive == true) {
        cout << "длина шага увеличина на " << settings.runeBoost * settings.currentRuneCount << endl;
        cout << "конец через " << settings.currentRuneState << endl;
    }
}
