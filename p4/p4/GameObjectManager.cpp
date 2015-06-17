#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "ServiceLocator.h"
#include "SoundProvider.h"


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

void GameObjectManager::removeAll()
{
	for (auto it = _items.cbegin(); it != _items.cend();)
		remove((it++)->first);
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
			auto item = (Item *)(it->second);
			if (item->getDirection() == gauche) {
				_jauge->moveNiveau(-1);
			}
			else if (item->getDirection() == droite) {
				_jauge->moveNiveau(1);
			}
			else if (item->getDirection() == mur) {
				Game::setGameState(Game::GameOver);
			}
			remove((it++)->first);
		}
		else
			++it;
	}
}

void GameObjectManager::supprItemsHorsEcran()
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
	static int idItem = 1;
	auto probaMur = Game::getDifficulte() * 5;
	auto nbMurMax = Game::getDifficulte();
	auto nbMur = 0;

	for (int route = 1; route <= 5; route++) {
		auto choixItem = rand() % 100;
		if (choixItem < 20) {
			Item *item = new Item();
			item->load("images/flecheG.png");
			item->setRoute(route);
			item->setDirection(gauche);
			add("FlecheG" + to_string(idItem), item);
			idItem++;
		}
		else if (choixItem < 40) {
			Item *item = new Item();
			item->load("images/flecheD.png");
			item->setRoute(route);
			item->setDirection(droite);
			add("FlecheD" + to_string(idItem), item);
			idItem++;
		}
		else if (choixItem < 40 + probaMur && nbMur < nbMurMax) {
			Item *item = new Item();
			item->load("images/brique.png");
			item->setRoute(route);
			item->setDirection(mur);
			add("Mur" + to_string(idItem), item);
			nbMur++;
			idItem++;
		}
		else if (choixItem < 100  ) {
			//rien
		}
	}
}

void GameObjectManager::defilement() {
	for (auto &item : _items) {
		auto route = item.second->getRoute();
		int vitesse = Game::getDifficulte() * 8;

		switch (Game::getDifficulte()) {
		case 1:
			item.second->scale(1.0039f, 1.0039f);
			break;
		case 2:
			item.second->scale(1.0041f, 1.0041f);
			break;
		case 3:
			item.second->scale(1.006f, 1.006f);
			break;
		case 4:
			item.second->scale(1.008f, 1.008f);
			break;
		}


		switch (route) {
		case 1:
			item.second->move(-0.60f*vitesse/8, vitesse);
			break;
		case 2:
			item.second->move(-0.20f*vitesse / 8, vitesse);
			break;
		case 3:
			item.second->move(0.07f*vitesse / 8, vitesse);
			break;
		case 4:
			item.second->move(0.20f*vitesse / 8, vitesse);
			break;
		case 5:
			item.second->move(0.57f*vitesse / 8, vitesse);
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

Score* GameObjectManager::getScore() const {
	return _score;
}

void GameObjectManager::setScore(Score *score) {
	_score = score;
}