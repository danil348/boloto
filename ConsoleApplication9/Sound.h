#pragma once
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_main.h>

using namespace std;

class Sound
{
public:
	bool isActive = true;
	Sound();
	~Sound();
	void addSoundEffect(const char* path);
	void playSoundEffect(const int which) const;
private:
	int audioRate = 22050;
	Uint16 audioFormat = AUDIO_S16SYS;
	int audioChannels = 2;
	int audioBuffers = 4096;
	vector<Mix_Chunk*> soundEffects;
};

