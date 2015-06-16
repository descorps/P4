#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include <sstream>

Clock chronoFPS;
Clock chronoClearItem;
Clock chronoDifficulte;
Clock chronoItem;
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
int Game::difficulte = 1;

const GameObjectManager& Game::getGameObjectManager()
{
	return Game::_gameObjectManager;
}


const int Game::getDifficulte() {
	return difficulte;
}

void Game::Start(void)
{
	srand((unsigned int)time(NULL));

	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Super biker of the dead III: THE REVENGE part 2");
	_mainWindow.setFramerateLimit(60);

	Score *score = new Score();
	_gameObjectManager.setScore(score);

	Jauge *jauge = new Jauge(0,1);
	jauge->load("images/jauge.png");
	jauge->setPosition((1024 / 2) - 405, WINDOW_HEIGHT - 93);
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

		if (chronoFPS.getElapsedTime().asMilliseconds() >= 50) {
			chronoFPS.restart();

			_gameObjectManager.getScore()->augmenterPoints(1);

			_gameObjectManager.getCycliste()->animation(88, 264, 88, 88);

			_gameObjectManager.defilement();
		}

		if (chronoItem.getElapsedTime().asSeconds() >= 1) {
			chronoItem.restart();
			_gameObjectManager.generateurItems();
		}

		if (chronoClearItem.getElapsedTime().asMilliseconds() >= 5000) {
			chronoClearItem.restart();
			_gameObjectManager.supprItemsHorsEcran();
		}

		if (chronoDifficulte.getElapsedTime().asSeconds() >= 20) {
			chronoDifficulte.restart();
			if (difficulte != 4)
				difficulte = difficulte + 1;
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
