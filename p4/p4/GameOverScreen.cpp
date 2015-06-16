#include "stdafx.h"
#include "GameOverScreen.h"


void GameOverScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture texture;
	if (texture.loadFromFile("images/gameover.png") != true)
	{
		return;
	}

	sf::Sprite sprite(texture);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}