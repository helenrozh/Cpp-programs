#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

struct V
{
	float dx, dy;
};

class Matter
{
public:
	int x, y;
	int w, h;
	float speed;
	V dir;
	bool isMove;

	String name;
	Texture texture;
	Sprite sprite;

	Matter(String F, int X, int Y, int W, int H)
	{
		name = F;
		w = W; h = H;
		texture.loadFromFile("src\\recources\\images\\" + F + ".png");
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setPosition((float)X, (float)Y);
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
};

class Entity : public Matter
{
public:
	int HP, maxHP;
	bool isAlive, isMove, isRestore;

	Entity(String F, int X, int Y, int W, int H, int MaxHP) : Matter(F, X, Y, W, H)
	{
		maxHP = MaxHP;
		HP = MaxHP;
		isAlive = true;
	}
};

class Player : public Entity
{
public:
	int money;
	float speed;
	int MP, maxMP;
	int maxGameTimeHealth;
	int maxGameTimeMana;
	bool healthRestoring;
	bool manaRestoring;
	float dex;  //dexterity

	Player(String F, int X, int Y, int W, int H, int MaxHP, int MaxMP) : Entity(F, X, Y, W, H, MaxHP)
	{
		dex = 1;			//dexterity is default
		maxGameTimeHealth = 0;
		maxGameTimeMana = 0;
		healthRestoring = true;
		manaRestoring = true;
		maxMP = MaxMP;
		MP = MaxMP;
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
			gameTime *= 2;
			if (HP < maxHP)
			{
				
					if ((int)gameTime > maxGameTimeHealth)
					{
						healthRestoring = true;
						maxGameTimeHealth = (int)gameTime;
					}
					if ((int)maxGameTimeHealth % 1 == 0 && healthRestoring)
					{
						HP += 1;
						healthRestoring = false;
					}

			}
			if (MP < maxMP)
			{

				if (abs ((int)gameTime - maxGameTimeMana) > 3)
				{
					manaRestoring = true;
					maxGameTimeMana = (int)gameTime;
				}
				if (manaRestoring)
				{
					MP += 1;
					manaRestoring = false;
				}

			}
		}
	}
};

#endif