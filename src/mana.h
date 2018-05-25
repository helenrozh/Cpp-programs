#ifndef MANA_H
#define MANA_H

#include "player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void increaseDexterity(Player& player, Clock gameTimeClock)
{
	player.MP -= 50;
	float gameTime = gameTimeClock.getElapsedTime().asSeconds();
	float currentTime = gameTime;
	player.dex = 3;
	while (currentTime - gameTime < 3)
	{
		currentTime = gameTimeClock.getElapsedTime().asSeconds();
	}
	player.dex = 1;
}

void manaUsage(Player& player, Clock gameTimeClock, RenderWindow& window)
{
	bool isPressed = false;
	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::Num1))
			{
				isPressed = true;
				player.MP -= 50;
				//increaseDexterity(player, gameTimeClock);
			}
		}
	}
	/*
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		isPressed = true;
		//player.MP -= 50;
		//increaseDexterity(player, gameTimeClock);
	}
	else
	{
		if (isPressed)
		{
			isPressed = false;
			player.MP -= 50;
		}
	}*/
}

#endif 
