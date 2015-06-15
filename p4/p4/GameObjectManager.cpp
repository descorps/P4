#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"



GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::add(std::string name, Item* item)
{
	_items.insert(std::pair<std::string, Item*>(name, item));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, Item*>::iterator results = _items.find(name);
	if (results != _items.end())
	{
		delete results->second;
		_items.erase(results);
	}
}

Item* GameObjectManager::get(std::string name) const
{
	std::map<std::string, Item*>::const_iterator results = _items.find(name);
	if (results == _items.end())
		return NULL;
	return results->second;

}

int GameObjectManager::getObjectCount() const
{
	return _items.size();
}


void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	
	for (auto &item : _items)
		item.second->draw(renderWindow);
	_cycliste->draw(renderWindow);
}

void GameObjectManager::collisionCycliste()
{
	for (auto &item : _items) {
		if (_cycliste->getSprite().getGlobalBounds().intersects(item.second->getSprite().getGlobalBounds()))
			;//remove(item.first);
	}
	
}

void GameObjectManager::generateurItems() {
	auto route = rand() % 5 + 1;
	Fleche *fleche = new Fleche();
	fleche->load("images/flecheG.png");
	fleche->setRoute(route);
	static int i = 1;

	char *nomFleche = "";

	add("Fleche" + to_string(i), fleche);
	i++;
}

void GameObjectManager::defilement() {
	for (auto &item : _items) {
		item.second->move(0, 8);
		item.second->scale(1.005f, 1.005f);
	}
}

Cycliste* GameObjectManager::getCycliste() {
	return _cycliste;
}

void GameObjectManager::setCycliste(Cycliste* cycliste) {
	_cycliste = cycliste;
}