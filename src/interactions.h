#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "player.h"
#include "defines.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;



void obstacles(Player& player, char c) {
	//up
	int i = (player.y - smallNum) / tileSize;
	int j = player.x / tileSize;
	if (TileMap[i][j] == c || ((TileMap[i][j + 1] == c) && (int((player.x + spiderSize) / tileSize) == j + 1)))
		if (player.dir.dy < 0) {
			player.y = i * tileSize + tileSize + smallNum;
			//return;
		}
	//down
	i = (player.y + spiderSize + smallNum) / tileSize;
	j = player.x / tileSize;
	if ((TileMap[i][j] == c) || ((TileMap[i][j + 1] == c) && (int((player.x + spiderSize) / tileSize) == j + 1)))
		if (player.dir.dy > 0) {
			player.y = i * tileSize - player.h - smallNum;
			//return;
		}
	//right
	i = player.y / tileSize;
	j = (player.x - smallNum) / tileSize;
	if (TileMap[i][j] == c || ((TileMap[i + 1][j] == c) && (int((player.y + spiderSize) / tileSize) == i + 1)))
		if (player.dir.dx < 0) {
			player.x = j * tileSize + tileSize + smallNum;
			//return;
		}
	//left
	j = (player.x + spiderSize + smallNum) / tileSize;
	if (TileMap[i][j] == c || ((TileMap[i + 1][j] == c) && (int((player.y + spiderSize) / tileSize) == i + 1)))
		if (player.dir.dx > 0) {
			player.x = j * tileSize - player.w - smallNum;
			//return;
		}
}

void collectMoney(Player& player, char c) {
	int i = (player.x + spiderSize / 2) / tileSize;
	int j = (player.y + spiderSize / 2) / tileSize;
	if (TileMap[j][i] == c) {
		TileMap[j][i] = ' ';
		player.money++;
	}
}

void interactionWithMap(Player& player) {
	obstacles(player, 'w');
	collectMoney(player, 'm');
}

#endif