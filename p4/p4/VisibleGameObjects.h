#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum Direction { gauche, droite, mur };

class ObjetVisible
{
public:
	ObjetVisible();
	void draw(RenderWindow & window) const;
	void load(string filename);
	void setPosition(float x, float y);
	virtual void setRoute(int numero) {};
	virtual int getRoute() { return 0; };
	virtual void moveRoute(Direction d) {};
	void move(float x, float y);
	void scale(float x, float y);
	Sprite getSprite();
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
	Cycliste(int orientation = 0, int route = 3);
	void animation(int tailleSprite, int top, int width, int height);
	void setRoute(int numero) override;
	int getRoute() override;
	void moveRoute(Direction d) override;
private:
	int orientation;
	int route;
};


class Item : public ObjetVisible
{
public :
	Item(int distance = 0, Direction direction = gauche);
	void setRoute(int numero);
	int getRoute();
	Direction getDirection();
	void setDirection(Direction direction);
private:
	int distance;
	int route;
	Direction direction;
};

class Jauge : public ObjetVisible
{
public:
	Jauge(int niveau = 0, int difficulte = 1);
	void remplirJauge(RenderWindow & window);
	void moveNiveau(int niveau);
	int getNiveau();
private:
	int niveau;
	int difficulte;
};

class Score : public ObjetVisible
{
public:
	Score(int points = 0);
	void augmenterPoints(int montant);
	void afficherScore(RenderWindow &window);
private:
	int points;
	Font font;
};

