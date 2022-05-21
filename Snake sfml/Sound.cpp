#include "Sound.h"

Sound::Sound()
{
	if (!bgmusic.loadFromFile("Music.wav"))
		return;
	music.setBuffer(bgmusic);
	music.setLoop(true);

	if (!snlose.loadFromFile("Defeat.wav"))
		return;
	lose.setBuffer(snlose);

	if (!eatapple.loadFromFile("Scored.wav"))
		return;
	eat.setBuffer(eatapple);
}

void Sound::PlayEat()
{
	eat.play();
}

void Sound::PlayLose()
{
	lose.play();
}

void Sound::PlayMusic()
{
	music.play();
}

void Sound::StopMusic()
{
	if (music.getStatus() == sf::Sound::Status::Playing)
	{
		music.stop();
	}
}