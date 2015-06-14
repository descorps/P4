#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Pang!");

	cycliste.load("images/bike.png");
	cycliste.setPosition((1024 / 2) - 45, 700);

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
	while (_mainWindow.pollEvent(currentEvent))
	{

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
			sf::Event currentEvent;
			while (_mainWindow.pollEvent(currentEvent))
			{
				_mainWindow.clear(sf::Color(0, 0, 0));
				cycliste.draw(_mainWindow);
				_mainWindow.display();

				if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

				if (currentEvent.type == sf::Event::KeyPressed)
				{
					if (currentEvent.key.code == sf::Keyboard::Key::Escape) ShowMenu();
				}

				if (currentEvent.type == sf::Event::KeyPressed)
				{


					cout << "bouton presse" << endl;

					if (currentEvent.key.code == sf::Keyboard::Key::Left)
						cycliste.mouvement(gauche);

					if (currentEvent.key.code == sf::Keyboard::Key::Right)
						cycliste.mouvement(droite);

				}
			}



			break;
		}
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
Cycliste Game::cycliste;