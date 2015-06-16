#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include <sstream>

Clock chrono;
Clock chrono2;

const GameObjectManager& Game::getGameObjectManager()
{
	return Game::_gameObjectManager;
}


void Game::Start(void)
{
	srand((unsigned int)time(NULL));

	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Pang!");
	_mainWindow.setFramerateLimit(60);

	Score *score = new Score();
	_gameObjectManager.setScore(score);

	Jauge *jauge = new Jauge(0,1);
	jauge->load("images/jauge.png");
	jauge->setPosition((1024 / 2) - 430, WINDOW_HEIGHT - 118);
	_gameObjectManager.setJauge(jauge);
	
	Cycliste *cycliste = new Cycliste();
	cycliste->load("images/cyclisteM.png");
	/* /!\ le sprite du cycliste doit faire 352 pixels */
	cycliste->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 112);
	_gameObjectManager.setCycliste(cycliste);

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

		if (chrono.getElapsedTime().asMilliseconds() >= 50) {
			chrono.restart();

			_gameObjectManager.getScore()->augmenterPoints(10);

			_gameObjectManager.getCycliste()->animation(88, 264, 88, 88);
			_gameObjectManager.generateurItems();

			_gameObjectManager.defilement();
		}

		if (chrono2.getElapsedTime().asMilliseconds() >= 5000) {
			chrono2.restart();
			_gameObjectManager.supprItemsHorsEcran();
		}

		_gameObjectManager.collisionCycliste();

		_gameObjectManager.drawAll(_mainWindow);

		_gameObjectManager.getScore()->afficherScore(_mainWindow);
		
		_mainWindow.display();

		if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Key::Escape)
				ShowMenu();

			if (currentEvent.key.code == sf::Keyboard::Key::Left)
				_gameObjectManager.getCycliste()->moveRoute(gauche);

			if (currentEvent.key.code == sf::Keyboard::Key::Right)
				_gameObjectManager.getCycliste()->moveRoute(droite);
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
