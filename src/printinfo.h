#ifndef PRINTINFO_H
#define PRINTINFO_H

#include "player.h"
#include "view.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


void printInfoIfAlive(Player& player, RenderWindow& window, Sprite moneyIndicatorSprite, Sprite healthIndicatorSprite, Text infoText)
{
	int x0 = (int)view.getCenter().x - screenWidth / 2;
	int y0 = (int)view.getCenter().y - screenHeight / 2;

	RectangleShape healthBar;
	healthBar.setOutlineColor(Color::Black);
	healthBar.setOutlineThickness(2);
	Color healthBarColor1(169, 169, 169);
	Color healthBarColor2(255, 165, 0);

	moneyIndicatorSprite.setPosition((float)x0 + 10, (float)y0 + 52);
	window.draw(moneyIndicatorSprite);

	healthIndicatorSprite.setPosition((float)x0 + 10, (float)y0 + 7);
	window.draw(healthIndicatorSprite);

	ostringstream info1;
	info1 << player.money;
	infoText.setString(info1.str());
	infoText.setPosition((float)x0 + 60, (float)y0 + 47);
	window.draw(infoText);

	healthBar.setPosition(Vector2f((float)x0 + 60, (float)y0 + 10));
	healthBar.setFillColor(healthBarColor1);
	healthBar.setSize(Vector2f(250, 32));
	window.draw(healthBar);

	if (player.HP > player.maxHP / 2)
	{
		healthBar.setFillColor(Color::Green);
	}
	else
	{
		if (player.HP > player.maxHP / 4)
		{
			healthBar.setFillColor(healthBarColor2);
		}
		else
		{
			healthBar.setFillColor(Color::Red);
		}
	}
	healthBar.setSize(Vector2f(250 * (float)player.HP / player.maxHP, 32));
	window.draw(healthBar);

	ostringstream info2;
	info2 << player.HP;
	infoText.setString(info2.str());
	infoText.setPosition((float)x0 + 60, (float)y0 + 5);
	window.draw(infoText);
}

void printInfoIfDead(RenderWindow& window, float gameTime, Text infoText, Sprite youDiedSprite)
{
	int x0 = (int)view.getCenter().x - screenWidth / 2;
	int y0 = (int)view.getCenter().y - screenHeight / 2;

	youDiedSprite.setPosition((float)x0, (float)y0 + 200);
	window.draw(youDiedSprite);

	infoText.setCharacterSize(20);
	infoText.setString("Press \"Space\" to continue");
	infoText.setPosition((float)x0 + screenWidth - 300, (float)y0 + screenHeight - 30);
	window.draw(infoText);

	int hours = (int)gameTime / 3600;
	int minutes = (int)gameTime / 60;
	int seconds = (int)gameTime % 60;

	string timeStr = "You were alive for ";
	if (hours != 0)
	{
		ostringstream info;
		info << hours;
		timeStr = timeStr + info.str() + "h ";
	}
	if (minutes != 0)
	{
		ostringstream info;
		info << minutes;
		timeStr = timeStr + info.str() + "m ";
	}
	if (seconds != 0)
	{
		ostringstream info;
		info << seconds;
		timeStr = timeStr + info.str() + "s ";
	}
	infoText.setString(timeStr);
	infoText.setPosition((float)x0 + (screenHeight - timeStr.length()) / 2, (float)y0 + screenHeight / 2 + 100);
	window.draw(infoText);

	infoText.setCharacterSize(40);
}

#endif