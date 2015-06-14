#include "VisibleGameObjects.h"
#include "stdafx.h"

ObjetVisible::ObjetVisible()
{
	estCharge = false;
}

/* Objet visible */
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

/* Cycliste */
Cycliste::Cycliste(int orientation, int position) :
	orientation(orientation),
	position(position)
{
}

void Cycliste::mouvement(Direction d) {
	switch (d)
	{
	case gauche:
		sprite.move(- WINDOW_WIDTH / 5, 0);
		break;
	case droite:
		sprite.move(WINDOW_WIDTH / 5, 0);
		break;

	}
}

/* Objets qui défilents */
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

/* Jauge */
Jauge::Jauge(int niveau, int tolerance) :
	niveau(niveau),
	tolerance(tolerance)
{
}
