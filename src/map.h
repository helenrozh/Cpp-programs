#ifndef MAP_H
#define MAP_H

#include "defines.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;



String TileMap[mapHeight] = {
	"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
	"w        mmm                   w",
	"w       mmmmmm                 w",
	"w               w              w",
	"w           wwww               w",
	"w          www w               w",
	"w         wwww w               w",
	"w   www     ww w               w",
	"w                              w",
	"w   www      www               w",
	"w                              w",
	"w ssssssssss                   w",
	"w s   s    s                   w",
	"w s s s smms                   w",
	"w   s   smms                   w",
	"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
};

void drawMap(Sprite s_map, RenderWindow& window) {
	window.clear(Color::White);
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, tileSize, tileSize));
			if (TileMap[i][j] == 'm')  s_map.setTextureRect(IntRect(0, 1 * tileSize, tileSize, tileSize));
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 2 * tileSize, tileSize, tileSize));
			if (TileMap[i][j] == 'w')  s_map.setTextureRect(IntRect(0, 3 * tileSize + 1, tileSize, tileSize));

			s_map.setPosition(j * tileSize, i * tileSize);
			window.draw(s_map);
		}
	}
}

#endif