#pragma once
#include <string>

using namespace std;

struct MapElements {
    static int const size = 15;
    char Elements[size] = {
        char(191), // ┐ 0
        char(192), // └ 1
        char(193), // ┴ 2 
        char(194), // ┬ 3
        char(195), // ├ 4 
        char(196), // ─ 5
        char(197), // ┼ 6
        char(198), // ╞ 7 
        char(217), // ┘ 8
        char(218), // ┌ 9 
        char(179), // │ 10
        char(180), // ┤ 11
        char(181), // ╡ 12
        char(4),
        //char(15), // 13
        char(254u), // 14
    };
};

struct Highground
{
public:
    int x;
    int y;
    bool hasRune = false;
};

struct BestRes
{
    int res = INT_MAX;
    int row = INT_MAX;
    int col = INT_MAX;
    int mosqCount = 1;
};

struct Settings
{
public:
    int score = 1;

    //--------------------------
    int highgroundLVL = 4;
    int maxHighgroundLVL = 20;
    //--------------------------

    //--------------------------
    int playerCurrentStep = 5;
    int maxPlayerMaxStep = 20;
    //--------------------------

    //--------------------------
    int mosquitoCurrentStep = 1;
    int maxMosquitoMaxStep = 10;

    int mosquitoCount = 1;
    int maxMosquitoCount = 5;

    int mosquitoCountLife = 1;

    bool mosquitoIntellect = false;
    //--------------------------

    //--------------------------
    int runeLvl = 1;
    int maxRuneLvl = 5;

    int chanceToCreateRune = 5; // 5%
    int maxChanceToCreateRune = 20;

    int runeCount = 1;
    int maxRuneCount = 5;

    int runeBoost = 1;
    int maxRuneBoost = 5;

    int currentRuneCount = 0;

    int currentRuneState;

    bool runeIsActive = false;
    //--------------------------

    //--------------------------
    const int fonts = 5;
    int fontSizeCount = 4;
    //{ 16, 18, 20, 24, 28, 36, 72 }
    int fontSize[7][2] = {
        {16,63},
        {18,56},
        {20,50},
        {24,42},
        {28,36},
        {36,28}
        /*{72,14}*/
    };
    int currentFontSize = 28;
    //--------------------------
    // максимальные и минимальные размеры поля
    int maxRow = 30;
    int maxCol = 44;
    int minRow = 5;
    int minCol = 5;
};

struct FontCases
{
    //fontSize, offsetX, offsetY, width, heigth, fontInfo.dwFontSize.Y
    int font[7][6] = {
        {16, 6, 17, 24, 16},
        {18, 8, 19, 24, 18},
        {20, 10, 21, 27, 20},
        {24, 12, 23, 33, 24},
        {28, 14, 27, 39, 28},
        {36, 16, 35, 51, 36}
        //{72, 32, 71, 102, 72}
    };
};