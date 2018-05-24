#ifndef WEAPON_H
#define WEAPON_H

#include "defines.h"
#include "player.h"

#include <list>

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

float maxGameTimeWeapon = 0;
bool isShooting = true;

class Weapon : public Matter
{
	public:
		int damage;
		int range;
		int x0, y0;
		bool isFriendly;

		Weapon(String F, int X, int Y, int W, int H, int Damage, float DX, float DY, int Range, bool isF) : Matter(F,X,Y,W,H)
		{
			isFriendly = isF;
			x0 = X;
			y0 = Y;
			x = x0;
			y = y0;
			damage = Damage;
			dir.dx = DX;
			dir.dy = DY;
			range = Range;
			sprite.setOrigin(Vector2f(w / 2, h / 2));
			sprite.setRotation(atan2(DY, DX) * 100);
			//sprite.setRotation(100);
		}

		bool update(float time)
		{
			float hip = sqrt(dir.dx * dir.dx + dir.dy * dir.dy);
			x = x + time * weaponSpeed * strangeConst2 * dir.dx / hip;
			y = y + time * weaponSpeed * strangeConst2 * dir.dy / hip;
			sprite.setPosition(x, y);
			if ((abs(x - x0) < range * abs(dir.dx / hip)) && (abs(y - y0) < range * abs(dir.dy / hip)))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
};


void shootingPlayer(Player player, RenderWindow& window, list<Weapon*>& weapons, float time, float gameTime)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (gameTime - maxGameTimeWeapon > 0.5 / player.dex)
		{
			isShooting = true;
			maxGameTimeWeapon = gameTime;
		}
		//cout << isShooting << "\n";
		if (isShooting)
		{
			isShooting = false;
			Vector2i pixelPos = Mouse::getPosition(window);  //забираем коорд курсора
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			float dX = pos.x - player.x - player.w / 2;
			float dY = pos.y - player.y - player.h / 2;
			//cout << dX << " " << dY << "\n";
			weapons.push_back(new Weapon("web", player.x + player.w / 2, player.y + player.h / 2, 25, 25, 20, dX, dY, 512, true));
		}
	}

	list<Weapon*>::iterator listEnd = weapons.end();
	for (list<Weapon*>::iterator it = weapons.begin(); it != listEnd; )
	{
		if ((*it)->update(time))
		{
			delete(*it);
			it = weapons.erase(it);
			//listEnd = weapons.end();
		}
		else
		{
			window.draw((*it)->sprite);
			it++;
		}
	}
}

#endif