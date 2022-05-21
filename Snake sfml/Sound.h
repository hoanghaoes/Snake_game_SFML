#pragma once
#include <SFML/Audio.hpp>

class Sound
{
public:
	Sound();

	void PlayEat();
	void PlayLose();
	void PlayMusic();
	void StopMusic();

private:
	sf::SoundBuffer bgmusic;
	sf::SoundBuffer snlose;
	sf::SoundBuffer eatapple;
	sf::Sound music;
	sf::Sound lose;
	sf::Sound eat;
};

