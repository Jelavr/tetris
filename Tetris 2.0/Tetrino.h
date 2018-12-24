#pragma once
#include <cstdint>
#include <stdlib.h> 
#include <time.h>
#include "SoundPlayer.h"



const static uint8_t width = 10;
const static  uint8_t height = 24;
const static uint8_t size = 4;
enum colors {blue , red, purple, green, cyan, pink, white, defaultColor};
const static uint8_t possibleShape[7][4]
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};
/*
	desinged so x can only be 0 or 1 and y between 0 and 3 for all shapes :
	NOTE: 2nd element will always be the center of rotation.

	0 1
	2 3
	4 5
	6 7

	- 1		- -
	- 3		2 -
	- 5		4 5
	- 7		- 7 etc...

	0, 0 ,1 , 1
	1, 2 ,2 ,3
*/

class Tetrino
{
public:

	Tetrino();

	int8_t x(int8_t i) const;
	int8_t y(int8_t i) const;
	colors color() const;

	void rotate(); //rotate 90 degrees clockwise
	void fall();
	void moveLeft();
	void moveRight();

	void randomShape();

private:

	int8_t x_[4];
	int8_t y_[4];
	colors color_;
	SoundPlayer soundPlayer_;
};
