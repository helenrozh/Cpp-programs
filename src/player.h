#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int maxGameTimeRestoring = 0;
bool healthRestoring = true;

struct V
{
	float dx, dy;
};

class Entity
{
public:
	int x, y;
	int w, h;
	int HP, maxHP;
	float speed;
	V dir;
	bool isAlive, isMove, isRestore;

	String name;
	Texture texture;
	Sprite sprite;

	Entity(String F, int X, int Y, int W, int H, int MaxHP)
	{
		name = F;
		w = W; h = H;
		texture.loadFromFile("src\\recources\\images\\" + F + ".png");
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setPosition((float)X, (float)Y);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		maxHP = MaxHP;
		HP = maxHP;
		isAlive = true;
	}
};

class Player : public Entity
{
public:
	int money;
	float speed;

	Player(String F, int X, int Y, int W, int H, int MaxHP) : Entity(F, X, Y, W, H, MaxHP)
	{
		speed = 1;		//speed is default
		money = 0;

	}

	void update(float gameTime)
	{
		x += (int)dir.dx;
		y += (int)dir.dy;
		sprite.setPosition((float)x, (float)y);
		if (HP <= 0)
		{
			isAlive = false;
			sprite.setTextureRect(IntRect(0, 8 * h, w, h));
			dir.dx = 0;
			dir.dy = 0;
		}
		else
		{
			if (HP < maxHP)
			{
				gameTime *= 2;
				
					if ((int)(gameTime) != maxGameTimeRestoring)
					{
						healthRestoring = true;
					}
					if ((int)gameTime > maxGameTimeRestoring)
					{
						maxGameTimeRestoring = (int)gameTime;
					}
					if ((int)maxGameTimeRestoring % 1 == 0 && healthRestoring)
					{
						HP += 1;
						healthRestoring = false;
					}

			}
		}
	}
};

#endif