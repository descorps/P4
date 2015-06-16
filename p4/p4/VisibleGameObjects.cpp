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
		if ((sprite.getPosition().x + x < WINDOW_WIDTH) && (sprite.getPosition().x + x > 0)) {
			sprite.move(x, y);
		}
}

Sprite ObjetVisible::getSprite()
{
	return sprite;
}

void ObjetVisible::scale(float x, float y) {
	if (estCharge)
		sprite.scale(x, y);
}

/* Cycliste */
Cycliste::Cycliste(int orientation, int route) :
	orientation(orientation),
	route(route)
{
}

void Cycliste::animation(int tailleSprite, int top, int width, int height) {
	static int compteurAnim = 0;
	compteurAnim = (compteurAnim + 1) % 4;
	sprite.setTextureRect(IntRect(compteurAnim*tailleSprite, top, width, height));
}

void Cycliste::setRoute(int numero) {
	if ((numero <= 5) && (numero >= 1)) {
		route = numero;
		switch (numero) {
		case 1:
			setPosition(138.4f, sprite.getPosition().y);
			break;
		case 2:
			setPosition(303.2f, sprite.getPosition().y);
			break;
		case 3:
			setPosition(468, sprite.getPosition().y);
			break;
		case 4:
			setPosition(632.8f, sprite.getPosition().y);
			break;
		case 5:
			setPosition(797.6f, sprite.getPosition().y);
			break;
		}
	}
}

int Cycliste::getRoute() {
	return route;
}


void Cycliste::moveRoute(Direction d) { 
	switch (d) {
	case gauche:
		if (route != 1)
			setRoute(getRoute() - 1);
		break;
	case droite:
		if (route != 5)
			setRoute(getRoute() + 1);
		break;
	}
}


/* Items qui défilents */

void Item::setRoute(int numero) {
	if ((numero <= 5) && (numero >= 1)) {
		route = numero;
		switch (numero) {
		case 1:
			setPosition(138.4f, sprite.getPosition().y);
			break;
		case 2:
			setPosition(303.2f, sprite.getPosition().y);
			break;
		case 3:
			setPosition(468, sprite.getPosition().y);
			break;
		case 4:
			setPosition(632.8f, sprite.getPosition().y);
			break;
		case 5:
			setPosition(797.6f, sprite.getPosition().y);
			break;
		}
	}
}

int Item::getRoute() {
	return route;
}

Direction Fleche::getDirection() {
	return direction;
}
void Fleche::setDirection(Direction direction){
	this->direction = direction;
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
Jauge::Jauge(int niveau, int difficulte) :
	niveau(niveau),
	difficulte(difficulte)
{
}

void Jauge::remplirJauge(RenderWindow & window) {
	RectangleShape rectangleVert(sf::Vector2f(800, 50));
	rectangleVert.setPosition((1024 / 2) - 400, WINDOW_HEIGHT - 90);
	rectangleVert.setFillColor(sf::Color(100, 250, 50));
	window.draw(rectangleVert);

	RectangleShape rectangleRouge1(sf::Vector2f(80, 50));
	rectangleRouge1.setPosition((1024 / 2) - 400, WINDOW_HEIGHT - 85);
	rectangleRouge1.setFillColor(sf::Color(250, 0, 0));
	rectangleRouge1.scale(float(difficulte), 1);
	window.draw(rectangleRouge1);

	RectangleShape rectangleRouge2(sf::Vector2f(80, 50));
	rectangleRouge2.setOrigin(80, 0);
	rectangleRouge2.setPosition((1024 / 2) + 400, WINDOW_HEIGHT - 85);
	rectangleRouge2.setFillColor(sf::Color(250, 0, 0));
	rectangleRouge2.scale(float(difficulte), 1);
	window.draw(rectangleRouge2);

	this->draw(window);

	RectangleShape Curseur(sf::Vector2f(10, 45));
	Curseur.setPosition((1024 / 2) - 5 + 50 * float(niveau), WINDOW_HEIGHT - 80);
	Curseur.setFillColor(sf::Color(190,190,190));
	window.draw(Curseur);
}

void Jauge::moveNiveau(int modifNiveau) {
	this->niveau += modifNiveau;
}

int Jauge::getNiveau() {
	return niveau;
}