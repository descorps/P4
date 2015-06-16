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
	_jauge->remplirJauge(renderWindow);
}

void GameObjectManager::collisionCycliste()
{
	for (auto it = _items.cbegin(); it != _items.cend();) {
		if (_cycliste->getSprite().getGlobalBounds().intersects(it->second->getSprite().getGlobalBounds())) {
			auto fleche = (Fleche *)(it->second);
			if (fleche->getDirection() == gauche)
				_jauge->moveNiveau(-1);
			else if (fleche->getDirection() == droite)
				_jauge->moveNiveau(1);
			remove((it++)->first);
		}
		else
			++it;
	}
}

void GameObjectManager::supprFlechesHorsEcran()
{
	for (auto it = _items.cbegin(); it != _items.cend();) {
		if (it->second->getSprite().getGlobalBounds().top > 1000) {
			remove((it++)->first);
		}
		else
			++it;
	}
}

void GameObjectManager::generateurItems() {
	static int i = 1;
	auto alea = rand() % 100;
	if (alea > 75) {
		auto route = alea % 5 + 1;
		Fleche *fleche = new Fleche();
		fleche->load("images/flecheG.png");
		fleche->setRoute(route);
		fleche->setDirection(gauche);
		char *nomFleche = "";
		add("FlecheG" + to_string(i), fleche);
		i++;
	}
	else if (alea > 50) {
		auto route = alea % 5 + 1;
		Fleche *fleche = new Fleche();
		fleche->load("images/flecheD.png");
		fleche->setRoute(route);
		fleche->setDirection(droite);
		char *nomFleche = "";
		add("FlecheD" + to_string(i), fleche);
		i++;
	}
}

void GameObjectManager::defilement() {
	for (auto &item : _items) {
		auto route = item.second->getRoute();
		item.second->scale(1.005f, 1.005f);
		switch (route) {
		case 1:
			item.second->move(-0.75f, 8);
			break;
		case 2:
			item.second->move(-0.35f, 8);
			break;
		case 3:
			item.second->move(-0.08f, 8);
			break;
		case 4:
			item.second->move(0.05f, 8);
			break;
		case 5:
			item.second->move(0.45f, 8);
			break;
		}
	}
}

Cycliste* GameObjectManager::getCycliste() const {
	return _cycliste;
}

void GameObjectManager::setCycliste(Cycliste* cycliste) {
	_cycliste = cycliste;
}


Jauge* GameObjectManager::getJauge() const {
	return _jauge;
}


void GameObjectManager::setJauge(Jauge *jauge) {
	_jauge = jauge;
}

Score* GameObjectManager::getScore() {
	return _score;
}

void GameObjectManager::setScore(Score *score) {
	_score = score;
}