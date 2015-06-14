#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum Direction { gauche, droite };
enum TypeObstacle { mur };

class ObjetVisible
{
public:
	ObjetVisible();
	void draw(RenderWindow & window) const;
	void load(string filename);
	void setPosition(float x, float y);
private:
protected:
	Sprite sprite;
	Texture texture;
	string nomFichier;
	bool estCharge;
};

class Cycliste : public ObjetVisible
{
public:
	Cycliste(int orientation = 0, int position = 0);
private:
	int orientation;
	int position;

};

class Item : public ObjetVisible
{
public:
private:
	int distance;
};

class Fleche : public Item
{
public:
	Fleche(int distance = 0, Direction direction = gauche);
private:
	int distance;
	Direction direction;
};

class Obstacle : public Item
{
public:
	Obstacle(int distance = 0, TypeObstacle type = mur);
private:
	int distance;
	TypeObstacle type;
};

class Jauge : public ObjetVisible
{
public:
	Jauge(int niveau = 0, int tolerance = 45);
private:
	int niveau;
	int tolerance;
};