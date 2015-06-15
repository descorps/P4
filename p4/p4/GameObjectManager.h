#pragma once
#include "VisibleGameObjects.h"

class GameObjectManager
{
public:
	GameObjectManager();

	void add(std::string name, ObjetVisible* gameObject);
	void remove(std::string name);
	int getObjectCount() const;
	ObjetVisible* get(std::string name) const;
	bool collision(ObjetVisible *obj1, ObjetVisible *obj2) const;
	void drawAll(sf::RenderWindow& renderWindow);
private:
	std::map<std::string, ObjetVisible*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, ObjetVisible*> & p) const
		{
			delete p.second;
		}
	};
};