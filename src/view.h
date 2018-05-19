//I suppose thate map is bigger than screen size and tile is twice bigger than player

#ifndef VIEW_H
#define VIEW_H

#include "player.h"
#include "defines.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

View view;

void getCoordinatesForView(Player player) {
	int x = player.x;
	int y = player.y;
	if (x < screenWidth / 2 - player.w)
		x = screenWidth / 2 - player.w;
	if (y < screenHeight / 2 - player.h)
		y = screenHeight / 2 - player.h;
	if (x > mapWidth * tileSize - screenWidth / 2 - player.w)
		x = mapWidth * tileSize - screenWidth / 2 - player.w;
	if (y > mapHeight * tileSize - screenHeight / 2 - player.h)
		y = mapHeight * tileSize - screenHeight / 2 - player.h;

	view.setCenter(x + player.w, y + player.h);
}

#endif