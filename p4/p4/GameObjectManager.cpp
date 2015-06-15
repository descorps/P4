#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"



GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::add(std::string name, ObjetVisible* gameObject)
{
	_gameObjects.insert(std::pair<std::string, ObjetVisible*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, ObjetVisible*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

ObjetVisible* GameObjectManager::get(std::string name) const
{
	std::map<std::string, ObjetVisible*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, ObjetVisible*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

bool GameObjectManager::collision(ObjetVisible *obj1, ObjetVisible *obj2) const
{
	if (obj1->getSprite().getGlobalBounds().intersects(obj2->getSprite().getGlobalBounds()))
		return true;
	else
		return false;
}