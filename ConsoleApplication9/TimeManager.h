#pragma once

#include <ctime>
#include <time.h>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

class TimeManager
{
public:
	void startTime();
	void stopTime();
	string getGameTime();
private:

	SYSTEMTIME tmpTime, Time;
};

