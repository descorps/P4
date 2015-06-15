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

void ObjetVisible::move(float x, float y)
{
	if (estCharge)
		sprite.move(x, y);
}




/* Cycliste */
Cycliste::Cycliste(int orientation) :
	orientation(orientation)
{
}

void Cycliste::animation(int tailleSprite, int top, int width, int height) {
	static int compteurAnim = 0;
	compteurAnim = (compteurAnim + 1) % 4;
	sprite.setTextureRect(IntRect(compteurAnim*tailleSprite, top, width, height));
}

/* Items qui défilents */
void Item::scale(float x, float y) {
	if (estCharge)
		sprite.scale(x, y);
}

void Item::defilement(){
	move(0, 8);
	scale(1.005, 1.005);
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

/* Jauge */
Jauge::Jauge(int niveau, int tolerance) :
	niveau(niveau),
	tolerance(tolerance)
{
}
