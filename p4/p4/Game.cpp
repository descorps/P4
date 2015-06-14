#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Pang!");
	_mainWindow.setFramerateLimit(60);

	Cycliste *cycliste = new Cycliste();
	cycliste->load("images/bike.png");
	cycliste->setPosition((1024 / 2) - 45, 700);
	_gameObjectManager.add("Cycliste", cycliste);

	Fleche *fleche = new Fleche();
	fleche->load("images/fleche.png");
	fleche->setPosition((1024 / 2) - 45, 300);
	_gameObjectManager.add("Fleche", fleche);

	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState)
	{
	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}
	case Game::Playing:
	{
			_mainWindow.clear(sf::Color(0, 0, 0));

			sf::Texture texture;
			if (texture.loadFromFile("images/route.png") != true){
				return;
			}
			sf::Sprite sprite(texture);
			_mainWindow.draw(sprite);

			_gameObjectManager.drawAll(_mainWindow);
			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Key::Escape) ShowMenu();
			}

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Key::Left) {
					_gameObjectManager.get("Cycliste")->move(-WINDOW_WIDTH / 5, 0);

				}
				if (currentEvent.key.code == sf::Keyboard::Key::Right)
					_gameObjectManager.get("Cycliste")->move(WINDOW_WIDTH / 5, 0);
			}
		



		break;
	}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;