#include "VisibleGameObjects.h"
#include "stdafx.h"

ObjetVisible::ObjetVisible()
{
	estCharge = false;
}

/* Fonctions draw et load qui est la même pour tous les objets qui héritent de ObjetVisible */

void ObjetVisible::load(string nomFichier)
{
	if (texture.loadFromFile(nomFichier) == false)
	{
		nomFichier = "";
		estCharge = false;
	}
	else
	{
		nomFichier = nomFichier;
		sprite.setTexture(texture);
		estCharge = true;
	}
}

void ObjetVisible::draw(RenderWindow & window) const {
	if (estCharge)
	{
		window.draw(sprite);
	}
}

void ObjetVisible::setPosition(float x, float y)
{
	if (estCharge)
	{
		sprite.setPosition(x, y);
	}
}

Cycliste::Cycliste(int orientation, int position) :
	orientation(orientation),
	position(position)
{
}

Fleche::Fleche(int distance, Direction direction) :
	distance(distance),
	direction(direction)
{
}


Obstacle::Obstacle(int distance, TypeObstacle type) :
	distance(distance),
	type(type)
{
}

Jauge::Jauge(int niveau, int tolerance) :
	niveau(niveau),
	tolerance(tolerance)
{
}