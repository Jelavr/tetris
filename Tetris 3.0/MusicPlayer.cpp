#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(std::string musicName)
{
	music_.openFromFile(musicName);

	music_.play();
	music_.setVolume(25);
	music_.setLoop(true);

}

void MusicPlayer::stop()
{
	music_.pause();
}

