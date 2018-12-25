#pragma once
#include <string>
#include <SFML/Audio.hpp>

class MusicPlayer
{
public:
	MusicPlayer(std::string musicName);
	void stop();
private:
	sf::Music music_;
};