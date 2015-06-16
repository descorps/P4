#include "stdafx.h"
#include "Game.h"
#include <sstream>

/* Objet visible */
ObjetVisible::ObjetVisible()
{
	estCharge = false;
}

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
		sprite.setOrigin(25, 25);
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

Sprite ObjetVisible::getSprite() const
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
	sprite.setOrigin(float(tailleSprite/2),  float(tailleSprite));
	sprite.setRotation(float(5* Game::getGameObjectManager().getJauge()->getNiveau() ));
}

void Cycliste::setRoute(int numero) {
	if ((numero <= 5) && (numero >= 1)) {
		route = numero;
		switch (numero) {
		case 1:
			setPosition(182.4f, sprite.getPosition().y);
			break;
		case 2:
			setPosition(347.2f, sprite.getPosition().y);
			break;
		case 3:
			setPosition(512, sprite.getPosition().y);
			break;
		case 4:
			setPosition(676.8f, sprite.getPosition().y);
			break;
		case 5:
			setPosition(841.6f, sprite.getPosition().y);
			break;
		}
	}
}

int Cycliste::getRoute() const {
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
Item::Item(int distance, Direction direction) :
	distance(distance),
	direction(direction)
{
}

void Item::setRoute(int numero) {
	if ((numero <= 5) && (numero >= 1)) {
		route = numero;
		switch (numero) {
		case 1:
			setPosition(240, -40);
			break;
		case 2:
			setPosition(365, -40);
			break;
		case 3:
			setPosition(505, -40);
			break;
		case 4:
			setPosition(655, -40);
			break;
		case 5:
			setPosition(782, -40);
			break;
		}
	}
}

int Item::getRoute() const {
	return route;
}


void Item::setDirection(Direction direction){
	this->direction = direction;
}

Direction Item::getDirection() const {
	return direction;
}


/* Jauge */
Jauge::Jauge(int niveau, int difficulte) :
	niveau(niveau)
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
	rectangleRouge1.scale(float(Game::getDifficulte()), 1);
	window.draw(rectangleRouge1);

	RectangleShape rectangleRouge2(sf::Vector2f(80, 50));
	rectangleRouge2.setOrigin(80, 0);
	rectangleRouge2.setPosition((1024 / 2) + 400, WINDOW_HEIGHT - 85);
	rectangleRouge2.setFillColor(sf::Color(250, 0, 0));
	rectangleRouge2.scale(float(Game::getDifficulte()), 1);
	window.draw(rectangleRouge2);

	this->draw(window);

	RectangleShape Curseur(sf::Vector2f(10, 45));
	Curseur.setPosition((1024 / 2) - 5 + 50 * float(niveau), WINDOW_HEIGHT - 80);
	Curseur.setFillColor(sf::Color(190,190,190));
	window.draw(Curseur);

	if ((1024 / 2) - 5 + 50 * niveau > ((1024 / 2) + 400 - 80)*difficulte
		|| (1024 / 2) - 5 + 50 * niveau < ((1024 / 2) - 400 + 80)*difficulte)
		Game::setGameState(Game::GameOver);
}

void Jauge::moveNiveau(int modifNiveau) {
	this->niveau += modifNiveau;
}

int Jauge::getNiveau() const {
	return niveau;
}


/* Score */
Score::Score(int points) :
	points(points)
{
};

void Score::augmenterPoints(int montant) {
	points += montant;
}



void Score::afficherScore(RenderWindow & window) {

	std::ostringstream os;
	os << points;

	Font font;
	font.loadFromFile("font/pixel.ttf");
	Text text;
	text.setPosition(10, 0);
	text.setFont(font);
	text.setString(os.str().c_str());
	text.setColor(Color::Red);
	text.setCharacterSize(32);
	window.draw(text);

}

