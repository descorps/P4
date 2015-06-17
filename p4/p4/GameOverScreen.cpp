#include "stdafx.h"
#include "GameOverScreen.h"
#include "Game.h"

void GameOverScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture texture;
	if (texture.loadFromFile("images/gameover.png") != true)
	{
		return;
	}

	sf::Sprite sprite(texture);

	renderWindow.draw(sprite);
	Game::getGameObjectManager().getScore()->afficherScore(renderWindow, WINDOW_WIDTH / 2 - 64, WINDOW_HEIGHT * 3 / 4, 2);

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