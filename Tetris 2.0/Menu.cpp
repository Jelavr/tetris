#include "Menu.h"

Menu::Menu(RenderWindow * window) : window_(window)
{}

void Menu::gameOver(std::string imageName)
{
	window_->clear();
	Texture t;
	t.loadFromFile(imageName);
	Sprite s(t);
	window_->setSize(Vector2u(852, 480));
	FloatRect visibleArea(0, 0, 852, 480);
	window_->setView(View(visibleArea));
	window_->draw(s);
	window_->display();

	Clock clock;
	clock.restart();

	soundPlayer.playSound("GameOver.ogg");
	while (clock.getElapsedTime().asSeconds() < 3)
	{
		// wait 
	}


	//display();

}
