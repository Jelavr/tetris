#include "Tetrino.h"

Tetrino::Tetrino()
{
	srand(time(NULL));
	randomShape();
}

int8_t Tetrino::x(int8_t i) const
{
		return x_[i];
}

int8_t Tetrino::y(int8_t i) const
{
	return y_[i];
}

colors Tetrino::color() const
{
	return color_;
}

void Tetrino::rotate()
{
	//pour eviter que le tetrino carrer rotate.
	if (color_ == white)
		return;

	int8_t rotCenterX = x_[1]; //the block table was designed that way so that the 2nd element would always be the center of rotation
	int8_t rotCenterY = y_[1];

	Tetrino backup = *this;

	for (int8_t i = 0; i < size; i++)
	{
		int8_t rotCenterYDistance = y_[i] - rotCenterY; //distance entre le centre de rotation et le point
		int8_t rotCenterXDistance = x_[i] - rotCenterX; //distance entre le centre de rotation et le point
		x_[i] = rotCenterX - rotCenterYDistance;
		y_[i] = rotCenterY + rotCenterXDistance; // + ici pcq l'axe des y est positive vers le bas ?
	}

	//checking if out of bounds
	for (int8_t i = 0; i < size; i++)
	{
		if (x_[i] < 0 || x_[i] >= width)
		{
			*this = backup;
			return;
		}
	}
	soundPlayer_.playSound("Rotate.wav");

}

void Tetrino::fall()
{
	for (uint8_t i = 0; i < size; i++)
		y_[i]++;
}

void Tetrino::moveLeft()
{
	for (uint8_t i = 0; i < size; i++)
	{
		if (x_[i] == 0)
			return;
	}
		
	for (uint8_t i = 0; i < size; i++)
		x_[i]--;
}

void Tetrino::moveRight()
{

	for (uint8_t i = 0; i < size; i++)
	{
		if (x_[i] == width - 1) //board width = 10 so 10-1 = 9
			return;
	}
	for (uint8_t i = 0; i < size; i++)
		x_[i]++;
}

void Tetrino::randomShape()
{
	
	uint8_t shapeNumber = rand() % 7;
	color_ = colors(shapeNumber);
	for (uint8_t i = 0; i < size; i++)
	{
		x_[i] = possibleShape[shapeNumber][i] % 2; // mod 2 va toujours donner 0 ou 1 ce qui est parfait pour faire la shape desire
		y_[i] = possibleShape[shapeNumber][i] / 2; //division entiere, coupe .5
	}
}
