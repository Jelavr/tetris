#include <SFML/Graphics.hpp>
#include <string>
#include "Tetrino.h"
#include "EventGestionnaire.h"
#include "GameBoard.h"
#include <iostream>
#include "Menu.h"


using namespace sf;

const std::string boardMusicFileName = "GameMusic.ogg";
const std::string gameName = "Tetris";
const uint8_t pixelSize = 33;
const uint16_t boardLength = width*pixelSize; //width = 10, defined in GameBoard
const uint16_t boardHeight = height*pixelSize; //height = 24, defined in GameBoard


int main()
{

	RenderWindow window(VideoMode(boardHeight, boardHeight), gameName);

	//tetrino and its backup
	Tetrino tetrino;
	Tetrino backupTetrino = tetrino;
	
	//Event gestions
	EventGestionnaire event(&window, &tetrino);

	//the game board and the textures.


	Menu menu(&window);


	while (window.isOpen())
	{
		GameBoard gb(&window, boardMusicFileName);
		gb.loadTetrinoTexture("squares.bmp");
		while (!gb.isGameOver())
		{
			//check events

			//falling time
			if (!gb.checkTime(&tetrino)) // to avoid 2 events happening at once
				event.checkEvents();

			//check obstacles
			if (gb.obstacleUnder(&tetrino))
			{
				if (tetrino.x(0) == backupTetrino.x(0)) //must not register hits from left or right.
				{
					//obstacle on the tetrino so we back it up and add it to the board.
					tetrino = backupTetrino;
					gb.addTetrino(&tetrino);

					//check lines, clear it if possible and play sound if cleared.
					gb.checkLines();

					//new random tetrino.
					tetrino.randomShape();
				}
				else //it was a left or right hit, we back up the tetrino but we do not add it to the board nor do we check lines.
					tetrino = backupTetrino;
			}

			//draw the game
			gb.drawBoard(&tetrino);
			// save last state
			backupTetrino = tetrino;
		}
		gb.~GameBoard();
		menu.gameOver("GameOver.jpg");
		window.close();
	}
}
