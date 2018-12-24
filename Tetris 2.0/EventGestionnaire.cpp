#include "EventGestionnaire.h"

EventGestionnaire::EventGestionnaire(RenderWindow * window, Tetrino * tet) :
	window_(window),
	tet_(tet)
{
}

void EventGestionnaire::checkEvents()
{
	while (window_->pollEvent(event_))
	{
		switch (event_.type)
		{
			case Event::Closed :
				window_->close();
				break;

			case Event::KeyPressed:
				switch (event_.key.code)
				{
					case Keyboard::Left:
						tet_->moveLeft();
						break;
					case Keyboard::Right:
						tet_->moveRight();
						break;
					case Keyboard::Up:
						tet_->rotate();
						break;
					case Keyboard::Down:
						tet_->fall();
						break;
				}
				break;
			
			default:
				break;
		}

	}
}
