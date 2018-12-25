#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>
#include "Tetrino.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"


using namespace sf;

class GameBoard
{
public:
	GameBoard(RenderWindow* window, std::string musicName);
	~GameBoard();
	
	void loadTetrinoTexture(std::string imageName);

	void addTetrino(Tetrino* tetrino);
	void checkLines();
	void drawBoard(Tetrino* tetrino);

	bool obstacleUnder(Tetrino* tetrino) const;
	bool isGameOver() const;

	bool checkTime(Tetrino* tet);

	
	colors& operator()(uint8_t i, uint8_t j);

private:
	RenderWindow* window_;

	Clock timer_; //for the falling time
	float delay_ = 0.3f;  //time in sec before tet goes down by one.
	colors** board_;

	Texture tetrinoT_;
	Sprite TetrinoS_;
	Sprite boardS_;
	Texture boardT_;

	MusicPlayer music_;
	SoundPlayer soundPlayer_;
	SoundPlayer soundPlayer2_;

	int score_ = 0;
	int level_ = 1;
};