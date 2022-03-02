#include "TimeManager.h"

void TimeManager::startTime()
{
    GetLocalTime(&tmpTime);
}

void TimeManager::stopTime()
{
    GetLocalTime(&Time);
}

string TimeManager::getGameTime()
{
    int t1 = tmpTime.wHour * 3600 + tmpTime.wMinute * 60 + tmpTime.wSecond;
    int t2 = Time.wHour * 3600 + Time.wMinute * 60 + Time.wSecond;

    int delta = t2 - t1;

    return to_string((delta % (60 * 60 * 24)) / (60 * 24)) + ":" + to_string((delta % (60 * 60)) / 60) + ":" + to_string(delta % 60);
}
