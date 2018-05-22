#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "player.h"
#include "defines.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int maxGameTimeSpikes = 0;
bool spikeDamage = true;

void spikes(Player& player, Map& map, char c, float gameTime) 
{
	int i = (player.x + spiderSize / 2) / tileSize;
	int j = (player.y + spiderSize / 2) / tileSize;

	gameTime *= 20;
	if (map.tile[j][i] == c)
	{
		if ((int)(gameTime) != maxGameTimeSpikes)
		{
			spikeDamage = true;
		}
		if ((int)gameTime > maxGameTimeSpikes)
		{
			maxGameTimeSpikes = (int)gameTime;
		}
		if ((int)maxGameTimeSpikes % 1 == 0 && spikeDamage)
		{
			player.HP -= 1;
			spikeDamage = false;
		}
	}
}

void obstacles(Player& player, Map& map, char c)
{
	//up
	int i = (player.y - smallNum) / tileSize;
	int j = player.x / tileSize;
	if (map.tile[i][j] == c || ((map.tile[i][j + 1] == c) && (int((player.x + spiderSize) / tileSize) == j + 1)))
		if (player.dir.dy < 0) 
		{
			player.y = i * tileSize + tileSize + smallNum;
		}
	//down
	i = (player.y + spiderSize + smallNum) / tileSize;
	j = player.x / tileSize;
	if ((map.tile[i][j] == c) || ((map.tile[i][j + 1] == c) && (int((player.x + spiderSize) / tileSize) == j + 1)))
		if (player.dir.dy > 0) 
		{
			player.y = i * tileSize - player.h - smallNum;
		}
	//right
	i = player.y / tileSize;
	j = (player.x - smallNum) / tileSize;
	if (map.tile[i][j] == c || ((map.tile[i + 1][j] == c) && (int((player.y + spiderSize) / tileSize) == i + 1)))
		if (player.dir.dx < 0) {
			player.x = j * tileSize + tileSize + smallNum;
		}
	//left
	j = (player.x + spiderSize + smallNum) / tileSize;
	if (map.tile[i][j] == c || ((map.tile[i + 1][j] == c) && (int((player.y + spiderSize) / tileSize) == i + 1)))
		if (player.dir.dx > 0) 
		{
			player.x = j * tileSize - player.w - smallNum;
		}
}

void collectMoney(Player& player, Map& map, char c)
{
	int i = (player.x + spiderSize / 2) / tileSize;
	int j = (player.y + spiderSize / 2) / tileSize;
	if (map.tile[j][i] == c) 
	{
		map.tile[j][i] = ' ';
		player.money++;
	}
}

void interactionWithMap(Player& player, Map& map, float gameTime)
{
	if (!player.isAlive)
		return;
	obstacles(player, map, 'w');
	collectMoney(player, map, 'm');
	spikes(player, map, 's', gameTime);
}

#endif