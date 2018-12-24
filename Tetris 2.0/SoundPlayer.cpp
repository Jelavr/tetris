#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	sound_.setVolume(25);
}

SoundPlayer::SoundPlayer(std::string soundName)
{
		buffer_.loadFromFile(soundName);
		sound_.setBuffer(buffer_);
		sound_.play();

		sound_.setVolume(25);

}

void SoundPlayer::playSound(std::string soundName)
{
		buffer_.loadFromFile(soundName);
		sound_.setBuffer(buffer_);
		sound_.play();
}
