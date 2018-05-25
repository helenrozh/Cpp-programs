#ifndef ENEMY_H
#define ENEMY_H

#include "defines.h"
#include "player.h"
#include "weapon.h"
#include <math.h>
#include "printinfo.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Enemy : public Entity
{
public:
	list<Weapon*>  weapons;
	bool isEnemyShooting;
	float maxGameTimeEnemyWeapon;

	Enemy(String F, int X, int Y, int W, int H, int MaxHP) : Entity(F, X, Y, W, H, MaxHP)
	{
		bool isEnemyShooting = true;
		float maxGameTimeEnemyWeapon = 0;
	};

	void shooting(Player& player, RenderWindow& window, float time, float gameTime)
	{
		if (abs(player.x - x) < 1600 && abs(player.y - y) < 1200 )
		{
			if (gameTime - maxGameTimeEnemyWeapon > 1)
			{
				isEnemyShooting = true;
				maxGameTimeEnemyWeapon = gameTime;
			}
			//cout << isShooting << "\n";
			if (isEnemyShooting)
			{
				isEnemyShooting = false;
				float dX = player.x + player.w / 2 - x - w / 2;
				float dY = player.y + player.h / 2 - y - h / 2;
				//cout << dX << " " << dY << "\n";
				weapons.push_back(new Weapon("sting", x + w / 2, y + h / 2, 25, 25, 30, dX, dY, 512, false));
			}
		}

		list<Weapon*>::iterator listEnd = weapons.end();
		for (list<Weapon*>::iterator it = weapons.begin(); it != listEnd; )
		{
			int wX = (*it)->x + (*it)->w / 2;
			int wY = (*it)->y + (*it)->h / 2;
			if ((wX > player.x + player.w / 2 - hit) && (wX < player.x + player.w / 2 + hit) && (wY > player.y + player.h / 2 - hit) && (wY < player.y + player.h / 2 + hit))
			{
				player.HP -= (*it)->damage;
				delete(*it);
				it = weapons.erase(it);
				listEnd = weapons.end();
			}
			else if ((*it)->update(time))
			{
				delete(*it);
				it = weapons.erase(it);
				listEnd = weapons.end();
			}
			else
			{
				window.draw((*it)->sprite);
				it++;
			}
		}
	}

	void update(float time, Player player, RenderWindow& window, list<Enemy*>& enemies, list<Enemy*>::iterator it)
	{
		/*if (HP <= 0)
		{
			//delete(*it);
			it = enemies.erase(it);
			return;
		}*/
		int dx = player.x + player.w - x - w;
		int dy = player.y + player.h - y - h;
		float hip = sqrt(dx * dx + dy * dy);
		if ((x - player.x) * (x - player.x) + (y - player.y) * (y - player.y) > tileSize)
		{
			x = x + strangeConst2 * time * dx / hip * 0.5;
			y = y + strangeConst2 * time * dy / hip * 0.5;
		}
		sprite.setPosition((float)x, (float)y);
		window.draw(sprite);
		smallHealthBar(*this, window);
	}
};

void interactionWithWeapon(list<Weapon*>& weapons, Enemy* enemy, RenderWindow& window,float time)
{
	list<Weapon*>::iterator listEnd = weapons.end();
	for (list<Weapon*>::iterator it = weapons.begin(); it != listEnd;)
	{
		int wX = (*it)->x + (*it)->w / 2;
		int wY = (*it)->y + (*it)->h / 2;
		if ((wX > enemy->x) && (wX < enemy->x + enemy->w) && (wY > enemy->y) && (wY < enemy->y + enemy->h) )
		{
			enemy->HP -= (*it)->damage;
			delete(*it);
			it = weapons.erase(it);
			//listEnd = weapons.end();
		}
		else
		{
			it++;
		}
	}
}
#endif