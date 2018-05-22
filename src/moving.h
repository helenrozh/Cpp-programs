#ifndef MOVING_H
#define MOVING_H

#include "player.h"
#include "defines.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;



void subsidiary(Player& player, int pixel, float time, float currentFrame) 
{
	switch ((int)(player.dir.dx * player.dir.dx + player.dir.dy * player.dir.dy)) 
	{
	case 1:
		player.dir.dx = player.dir.dx * time * player.speed * strangeConst2;
		player.dir.dy = player.dir.dy * time * player.speed * strangeConst2;
		break;
	case 2:
		player.dir.dx = player.dir.dx * time * player.speed * strangeConst2 * (float)divSqrt2;
		player.dir.dy = player.dir.dy * time * player.speed * strangeConst2 * (float)divSqrt2;
		break;
	}
	currentFrame += strangeConst1 * time;
	currentFrame = (int)currentFrame % framesNum + currentFrame - trunc(currentFrame);
	player.sprite.setTextureRect(IntRect(spiderSize * ((int)currentFrame), pixel, spiderSize, spiderSize));
	//cout << "(" << player.getPlayerX() << " " << player.getPlayerY() << ")";
};

void moving(Player& player, float time) 
{
	if (!player.isAlive)
		return;
	float currentFrame = 0;
	player.dir.dx = 0, player.dir.dy = 0;

	if (Keyboard::isKeyPressed(Keyboard::A))
		player.dir.dx -= 1;
	if (Keyboard::isKeyPressed(Keyboard::D))
		player.dir.dx += 1;
	if (Keyboard::isKeyPressed(Keyboard::W))
		player.dir.dy -= 1;
	if (Keyboard::isKeyPressed(Keyboard::S))
		player.dir.dy += 1;


	if (player.dir.dx == 1) 
	{
		switch ((int)player.dir.dy)
		{
		case 1:
			subsidiary(player, spiderSize * 5, time, currentFrame); break;
		case 0:
			subsidiary(player, spiderSize * 2, time, currentFrame); break;
		case -1:
			subsidiary(player, spiderSize * 6, time, currentFrame); break;
		}
	}
	if (player.dir.dx == 0) 
	{
		switch ((int)player.dir.dy)
		{
		case 1:
			subsidiary(player, 0, time, currentFrame); break;
		case 0:  break;
		case -1:
			subsidiary(player, spiderSize * 3, time, currentFrame); break;
		}
	}
	if (player.dir.dx == -1) 
	{
		switch ((int)player.dir.dy)
		{
		case 1:
			subsidiary(player, spiderSize * 4, time, currentFrame); break;
		case 0:
			subsidiary(player, spiderSize, time, currentFrame); break;
		case -1:
			subsidiary(player, spiderSize * 7, time, currentFrame); break;
		}
	}
};

#endif