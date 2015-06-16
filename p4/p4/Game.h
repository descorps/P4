#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"

class Game
{
public:
	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting, GameOver
	};
	static void Start();
	const static GameObjectManager& getGameObjectManager();
	static void setGameState(GameState gamestate);
	static void initialisation();
private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowGameOverScreen();
	static void ShowMenu();

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;

};