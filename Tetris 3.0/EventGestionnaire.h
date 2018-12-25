#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tetrino.h"


using namespace sf;



class EventGestionnaire
{
public:
	EventGestionnaire(RenderWindow* window, Tetrino* tet);

	void checkEvents();


private:
	RenderWindow* window_;
	Tetrino* tet_;
	Event event_;


};
