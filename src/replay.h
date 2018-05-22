#ifndef REPLAY_H
#define REPLAY_H

#include "player.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void replay(Player& player, Map& map, int mapNum)
{
	player.isAlive = true;
	player.HP = player.maxHP;
	player.x = 200;
	player.y = 200;
	player.money = 0;
	player.sprite.setTextureRect(IntRect(0, 0, spiderSize, spiderSize));

	map.readMap(mapNum);
}

#endif