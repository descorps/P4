#include "stdafx.h"
#include "SplashScreen.h"
#include "VisibleGameObjects.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	Clock chrono;
	sf::Texture texture;
	if (texture.loadFromFile("images/accueil.png") != true)
	{
		return;
	}
	sf::Sprite sprite(texture);

	sf::Texture textureCycliste;
	if (textureCycliste.loadFromFile("images/cyclisteM.png") != true)
	{
		return;
	}
	sf::Sprite spriteCycliste(textureCycliste);

	spriteCycliste.setTextureRect(IntRect(0, 88, 88, 88));
	spriteCycliste.setOrigin(44, 44);
	spriteCycliste.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/4);
	spriteCycliste.setScale(3, 3);


	int compteurAnim = 0;

	sf::Event event;
	chrono.restart();
	while (true)
	{
		if (chrono.getElapsedTime().asMilliseconds() >= 100) {
			compteurAnim = (compteurAnim +1) % 4;
			spriteCycliste.setTextureRect(IntRect(compteurAnim * 88, 88, 88, 88));
			chrono.restart();
		}

		renderWindow.draw(sprite);
		renderWindow.draw(spriteCycliste);

		renderWindow.display();

		//cout << compteurAnim << endl;

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