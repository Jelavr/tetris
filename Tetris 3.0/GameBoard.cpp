#include "GameBoard.h"



GameBoard::GameBoard(RenderWindow* window, std::string musicName) : window_(window), music_(musicName)
{
	board_ = new colors*[width];
	for (int i = 0; i < width; i++)
	{
		board_[i] = new colors[height];
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			board_[i][j] = defaultColor;
		}
	}

	
	boardT_.loadFromFile("GameBoard.bmp");
	boardS_.setTexture(boardT_);
	boardS_.setPosition(3 * 33, -38);

	timer_.restart();

}

//dealocate memory for the array
GameBoard::~GameBoard()
{
	for (short int i = 0; i < width; i++)
	{
		delete[] board_[i];
	}
	delete[] board_;
	music_.stop();
}

void GameBoard::loadTetrinoTexture(std::string imageName)
{
	tetrinoT_.loadFromFile(imageName);
	TetrinoS_.setTexture(tetrinoT_);
	TetrinoS_.setTextureRect(IntRect(32, 0, 32, 32));
}

void GameBoard::addTetrino(Tetrino* tetrino)
{
	for (uint8_t i = 0; i < size; i++)
	{
		board_[tetrino->x(i)][tetrino->y(i)] = tetrino->color();
	}
	soundPlayer_.playSound("Land.wav");
}

//maybe possible to optimise...
void GameBoard::checkLines()
{

	int8_t lines = height - 1;
	for (int8_t i = height-1; i > 0; i--)
	{
		bool fullLines = true;
		for (int8_t j = 0; j < width; j++)
		{
			if (board_[j][i] == defaultColor)
				fullLines = false;
			board_[j][lines] = board_[j][i];
		}
		if (!fullLines)
			lines--;
		else
		{
			int lastLevel = level_;
			score_ += 50 * (lines - i + 1);
			level_ = score_ / 256 + 1;
			if (lastLevel < level_)
				soundPlayer2_.playSound("level_up.wav");
		}
	}
	if (lines > 0)
		soundPlayer_.playSound("ClearLine.wav");
}

void GameBoard::drawBoard(Tetrino* tetrino)
{
	window_->clear();
	//draw the background
	window_->draw(boardS_);
	short int offsetX = 3;
	short int offsetY = -1;

	//draw current tetrino
	for (uint8_t i = 0; i < size; i++)
	{
		TetrinoS_.setTextureRect(IntRect(tetrino->color() * 33, 0, 33, 33));
		TetrinoS_.setPosition((tetrino->x(i) + offsetX)*33.f, (tetrino->y(i)+offsetY)*33.f);
		window_->draw(TetrinoS_);
	}

	//draw the board
	for (uint8_t i = 0; i < width; i++)
	{
		for (uint8_t j = 0; j < height; j++)
		{
			if (board_[i][j] != defaultColor)
			{
				TetrinoS_.setTextureRect(IntRect(board_[i][j] * 33 , 0, 33, 33));
				TetrinoS_.setPosition((i+offsetX) * 33.f, (j+offsetY) * 33.f);
				window_->draw(TetrinoS_);
			}
		}
	}

	//draw the score
	Text text;
	std::string s = "Score: " + std::to_string(score_) + " points";
	text.setString(s);
	Font font;
	font.loadFromFile("verdanab.ttf");
	text.setFont(font);
	text.setPosition((width+offsetX) * 33 + 33, 33);
	text.setFillColor(Color::Red);

	window_->draw(text);

	//draw the level
	s = "Level: " + std::to_string(level_);
	text.setString(s);
	text.setPosition((width + offsetX) * 33 + 33, 33*2);
	window_->draw(text);


	window_->display();
}

bool GameBoard::obstacleUnder(Tetrino * tetrino) const
{
	bool hasObstacle = false;
	for (int i = 0; i < size; i++)
	{
		bool hasBlock = board_[tetrino->x(i)][tetrino->y(i)] != defaultColor;
		bool bottomReached = tetrino->y(i) > height;
		if (hasBlock || bottomReached )
			hasObstacle = true;
	}
	return hasObstacle;
}

bool GameBoard::isGameOver() const
{
	for (int i = 0; i < width; i++)
	{
		if (board_[i][1] != defaultColor)
		{
			Clock clock;
			clock.restart();
			while (clock.getElapsedTime().asSeconds() < 1.0f)
			{
				// wait 
			}
			return true;
		}
	}	
	return false;
}

bool GameBoard::checkTime(Tetrino*  tet)
{
	if (timer_.getElapsedTime().asSeconds() > (delay_ - level_/100))
	{
		tet->fall();
		timer_.restart();
		return true;
	}
	return false;
}



colors& GameBoard::operator()(uint8_t i, uint8_t j)
{
	return board_[i][j];
}
