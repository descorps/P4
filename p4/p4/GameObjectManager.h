#pragma once
#include "VisibleGameObjects.h"

class GameObjectManager
{
public:
	GameObjectManager();

	void add(std::string name, Item* item);
	void remove(std::string name);
	int getObjectCount() const;
	Item* get(std::string name) const;
	void collisionCycliste();
	void supprFlechesHorsEcran();
	void drawAll(sf::RenderWindow& renderWindow);
	void generateurItems();
	void defilement();
	Cycliste* getCycliste();
	void setCycliste(Cycliste *cycliste);
	Jauge* getJauge();
	void setJauge(Jauge *jauge);
	Score* getScore();
	void setScore(Score *score);
private:
	std::map<std::string, Item*> _items;
	Cycliste *_cycliste;
	Jauge *_jauge;
	Score *_score;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, ObjetVisible*> & p) const
		{
			delete p.second;
		}
	};
};