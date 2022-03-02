#include "DataStorage.h"

using json = nlohmann::json;
using namespace std;

void DataStorage::getSetting(Settings &settings)
{
    ifstream writer;
    writer.open(file); 
    if (writer.is_open()) {
        writer >> JsonSetting;
    }
    writer.close();

    settings.chanceToCreateRune = JsonSetting["chanceToCreateRune"];
    settings.currentFontSize = JsonSetting["currentFontSize"];
    settings.currentRuneCount = JsonSetting["currentRuneCount"];
    settings.currentRuneState = JsonSetting["currentRuneState"];
    settings.fontSizeCount = JsonSetting["fontSizeCount"];
    settings.highgroundLVL = JsonSetting["highgroundLVL"];
    settings.maxChanceToCreateRune = JsonSetting["maxChanceToCreateRune"];
    settings.maxHighgroundLVL = JsonSetting["maxHighgroundLVL"];
    settings.maxMosquitoCount = JsonSetting["maxMosquitoCount"];
    settings.maxMosquitoMaxStep = JsonSetting["maxMosquitoMaxStep"];
    settings.maxPlayerMaxStep = JsonSetting["maxPlayerMaxStep"];
    settings.maxRuneBoost = JsonSetting["maxRuneBoost"];
    settings.maxRuneCount = JsonSetting["maxRuneCount"];
    settings.maxRuneLvl = JsonSetting["maxRuneLvl"];
    settings.mosquitoCount = JsonSetting["mosquitoCount"];
    settings.mosquitoCountLife = JsonSetting["mosquitoCountLife"];
    settings.mosquitoCurrentStep = JsonSetting["mosquitoCurrentStep"];
    settings.mosquitoIntellect = JsonSetting["mosquitoIntellect"];
    settings.playerCurrentStep = JsonSetting["playerCurrentStep"];
    settings.runeBoost = JsonSetting["runeBoost"];
    settings.runeCount = JsonSetting["runeCount"];
    settings.runeIsActive = JsonSetting["runeIsActive"];
    settings.runeLvl = JsonSetting["runeLvl"];
    settings.score = JsonSetting["score"];
}

void DataStorage::saveSetting(Settings settings)
{
    ofstream writer;
    writer.open(file);

    if (writer.is_open()) {
        JsonSetting["chanceToCreateRune"] = settings.chanceToCreateRune;
        JsonSetting["currentFontSize"] = settings.currentFontSize;
        JsonSetting["currentRuneCount"] = settings.currentRuneCount;
        JsonSetting["currentRuneState"] = settings.currentRuneState;
        JsonSetting["fontSizeCount"] = settings.fontSizeCount;
        JsonSetting["fonts"] = settings.fonts;
        JsonSetting["highgroundLVL"] = settings.highgroundLVL;
        JsonSetting["maxChanceToCreateRune"] = settings.maxChanceToCreateRune;
        JsonSetting["maxHighgroundLVL"] = settings.maxHighgroundLVL;
        JsonSetting["maxMosquitoCount"] = settings.maxMosquitoCount;
        JsonSetting["maxMosquitoMaxStep"] = settings.maxMosquitoMaxStep;
        JsonSetting["maxPlayerMaxStep"] = settings.maxPlayerMaxStep;
        JsonSetting["maxRuneBoost"] = settings.maxRuneBoost;
        JsonSetting["maxRuneCount"] = settings.maxRuneCount;
        JsonSetting["maxRuneLvl"] = settings.maxRuneLvl;
        JsonSetting["mosquitoCount"] = settings.mosquitoCount;
        JsonSetting["mosquitoCountLife"] = settings.mosquitoCountLife;
        JsonSetting["mosquitoCurrentStep"] = settings.mosquitoCurrentStep;
        JsonSetting["mosquitoIntellect"] = settings.mosquitoIntellect;
        JsonSetting["playerCurrentStep"] = settings.playerCurrentStep;
        JsonSetting["runeBoost"] = settings.runeBoost;
        JsonSetting["runeCount"] = settings.runeCount;
        JsonSetting["runeIsActive"] = settings.runeIsActive;
        JsonSetting["runeLvl"] = settings.runeLvl;
        JsonSetting["score"] = settings.score;
        writer << JsonSetting.dump(1);
    }
    writer.close();
}

void DataStorage::saveScore(int value, int row, int col, string time)
{
    string tmpNameRekord = to_string(row) + "x" + to_string(col);
    ofstream writer;
    writer.open(file);
    if (writer.is_open()) {
        JsonSetting["rekord"] += { tmpNameRekord, {
            {"value", value},
            {"row", row},
            {"col", col},
            {"time",time}
        } };
        writer << JsonSetting.dump(1);
    }
    writer.close();
}

void DataStorage::createFileJson(Settings settings)
{
    ofstream writer;
    writer.open(file);
    if (writer.is_open()) {
        JsonSetting = {
            {"score" , settings.score},
            {"highgroundLVL" , settings.highgroundLVL},
            {"maxHighgroundLVL" , settings.maxHighgroundLVL},
            {"playerCurrentStep" , settings.playerCurrentStep},
            {"maxPlayerMaxStep" , settings.maxPlayerMaxStep},
            {"mosquitoCurrentStep" , settings.mosquitoCurrentStep},
            {"maxMosquitoMaxStep" , settings.maxMosquitoMaxStep},
            {"mosquitoCount" , settings.mosquitoCount},
            {"maxMosquitoCount" , settings.maxMosquitoCount},
            {"mosquitoCountLife" , settings.mosquitoCountLife},
            {"mosquitoIntellect" , settings.mosquitoIntellect},
            {"runeLvl" , settings.runeLvl},
            {"maxRuneLvl" , settings.maxRuneLvl},
            {"chanceToCreateRune" , settings.chanceToCreateRune},
            {"maxChanceToCreateRune" , settings.maxChanceToCreateRune},
            {"runeCount" , settings.runeCount},
            {"maxRuneCount" , settings.maxRuneCount},
            {"runeBoost" , settings.runeBoost},
            {"maxRuneBoost" , settings.maxRuneBoost},
            {"currentRuneCount" , settings.currentRuneCount},
            {"currentRuneState" , settings.currentRuneState},
            {"runeIsActive" , settings.runeIsActive},
            {"fonts" , settings.fonts},
            {"fontSizeCount" , settings.fontSizeCount},
            {"currentFontSize" , settings.currentFontSize},
        };
        writer << JsonSetting.dump(4);
    }
    
    writer.close();
}

void DataStorage::refreshSetting(Settings &settings)
{
    ifstream writer;
    writer.open(DefoltFile);
    if (writer.is_open()) {
        writer >> JsonSetting;
    }
    writer.close();

    settings.chanceToCreateRune = JsonSetting["chanceToCreateRune"];
    settings.currentFontSize = JsonSetting["currentFontSize"];
    settings.currentRuneCount = JsonSetting["currentRuneCount"];
    settings.currentRuneState = JsonSetting["currentRuneState"];
    settings.fontSizeCount = JsonSetting["fontSizeCount"];
    settings.highgroundLVL = JsonSetting["highgroundLVL"];
    settings.maxChanceToCreateRune = JsonSetting["maxChanceToCreateRune"];
    settings.maxHighgroundLVL = JsonSetting["maxHighgroundLVL"];
    settings.maxMosquitoCount = JsonSetting["maxMosquitoCount"];
    settings.maxMosquitoMaxStep = JsonSetting["maxMosquitoMaxStep"];
    settings.maxPlayerMaxStep = JsonSetting["maxPlayerMaxStep"];
    settings.maxRuneBoost = JsonSetting["maxRuneBoost"];
    settings.maxRuneCount = JsonSetting["maxRuneCount"];
    settings.maxRuneLvl = JsonSetting["maxRuneLvl"];
    settings.mosquitoCount = JsonSetting["mosquitoCount"];
    settings.mosquitoCountLife = JsonSetting["mosquitoCountLife"];
    settings.mosquitoCurrentStep = JsonSetting["mosquitoCurrentStep"];
    settings.mosquitoIntellect = JsonSetting["mosquitoIntellect"];
    settings.playerCurrentStep = JsonSetting["playerCurrentStep"];
    settings.runeBoost = JsonSetting["runeBoost"];
    settings.runeCount = JsonSetting["runeCount"];
    settings.runeIsActive = JsonSetting["runeIsActive"];
    settings.runeLvl = JsonSetting["runeLvl"];
    settings.score = JsonSetting["score"];

    ofstream _writer;
    _writer.open(file);

    if (_writer.is_open()) {
        JsonSetting["chanceToCreateRune"] = settings.chanceToCreateRune;
        JsonSetting["currentFontSize"] = settings.currentFontSize;
        JsonSetting["currentRuneCount"] = settings.currentRuneCount;
        JsonSetting["currentRuneState"] = settings.currentRuneState;
        JsonSetting["fontSizeCount"] = settings.fontSizeCount;
        JsonSetting["fonts"] = settings.fonts;
        JsonSetting["highgroundLVL"] = settings.highgroundLVL;
        JsonSetting["maxChanceToCreateRune"] = settings.maxChanceToCreateRune;
        JsonSetting["maxHighgroundLVL"] = settings.maxHighgroundLVL;
        JsonSetting["maxMosquitoCount"] = settings.maxMosquitoCount;
        JsonSetting["maxMosquitoMaxStep"] = settings.maxMosquitoMaxStep;
        JsonSetting["maxPlayerMaxStep"] = settings.maxPlayerMaxStep;
        JsonSetting["maxRuneBoost"] = settings.maxRuneBoost;
        JsonSetting["maxRuneCount"] = settings.maxRuneCount;
        JsonSetting["maxRuneLvl"] = settings.maxRuneLvl;
        JsonSetting["mosquitoCount"] = settings.mosquitoCount;
        JsonSetting["mosquitoCountLife"] = settings.mosquitoCountLife;
        JsonSetting["mosquitoCurrentStep"] = settings.mosquitoCurrentStep;
        JsonSetting["mosquitoIntellect"] = settings.mosquitoIntellect;
        JsonSetting["playerCurrentStep"] = settings.playerCurrentStep;
        JsonSetting["runeBoost"] = settings.runeBoost;
        JsonSetting["runeCount"] = settings.runeCount;
        JsonSetting["runeIsActive"] = settings.runeIsActive;
        JsonSetting["runeLvl"] = settings.runeLvl;
        JsonSetting["score"] = settings.score;
        _writer << JsonSetting.dump(1);
    }
    _writer.close();
}
