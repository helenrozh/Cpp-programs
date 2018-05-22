#ifndef VIEW_H
#define VIEW_H

//I suppose thate map is bigger than screen size and tile is twice bigger than player

#include "player.h"
#include "defines.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

View view;

void getCoordinatesForView(Player player, Map& map)
{
	int x = player.x;
	int y = player.y;
	if (x < screenWidth / 2 - player.w)
	{
		x = screenWidth / 2 - player.w;
	}
	if (y < screenHeight / 2 - player.h)
	{
		y = screenHeight / 2 - player.h;
	}
	if (x > map.width * tileSize - screenWidth / 2 - player.w)
	{
		x = map.width * tileSize - screenWidth / 2 - player.w;
	}
	if (y > map.height * tileSize - screenHeight / 2 - player.h)
	{
		y = map.height * tileSize - screenHeight / 2 - player.h;
	}

	view.setCenter((float)x + player.w, (float)y + player.h);
}

#endif