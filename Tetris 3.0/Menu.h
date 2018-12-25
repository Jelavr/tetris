#pragma once
#include <SFML/Graphics.hpp>
#include "SoundPlayer.h"

using namespace sf;

class Menu
{
public:
	Menu(RenderWindow* window);

	void gameOver(std::string imageName);

private:
	RenderWindow* window_;
	SoundPlayer soundPlayer;
};