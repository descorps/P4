#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"
#include "SoundFileCache.h"

class SoundProvider : public IAudioProvider
{
public:

	SoundProvider();

	void playSound(std::string filename);
	void playSong(std::string filename, bool looping = false);
	void stopAllSounds();
	SoundFileCache getSoundFileCache();
	bool isSoundPlaying();
	bool isSongPlaying();

private:
	static const int MAX_SOUND_CHANNELS = 5;

	SoundFileCache _soundFileCache;
	sf::Sound   _currentSounds[MAX_SOUND_CHANNELS];
	std::string _currentSongName;
};