#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

struct V {
	int dx, dy;
};

class Player {
public:
	int x, y;
	int money;
	int HP, maxHP;
	float speed;
	int w, h;
	V dir;
	bool isAlive;

	String file;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String F, int X, int Y, int W, int H) {
		file = F;
		w = W; h = H;
		image.loadFromFile("src\\recources\\images\\" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setPosition(X, Y);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		speed = 1;		//speed is default
		money = 0;
		HP = 100;
		maxHP = 100;
		isAlive = true;
	}

	void update(float time) {
		x += dir.dx;
		y += dir.dy;
		sprite.setPosition(x, y);
	}
};

#endif