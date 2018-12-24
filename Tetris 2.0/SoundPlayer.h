#pragma once
#include <SFML/Audio.hpp>

class SoundPlayer
{
public:
	SoundPlayer();
	SoundPlayer(std::string soundName);

	void playSound(std::string soundName);
private:
	sf::SoundBuffer buffer_;
	sf::Sound sound_;
};