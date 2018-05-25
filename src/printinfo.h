#ifndef PRINTINFO_H
#define PRINTINFO_H

#include "player.h"
#include "view.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


void printInfoIfAlive(Player& player, RenderWindow& window, Sprite moneyIndicatorSprite, Sprite healthIndicatorSprite, Sprite manaIndicatorSprite, Text infoText)
{
	int x0 = (int)view.getCenter().x - screenWidth / 2;
	int y0 = (int)view.getCenter().y - screenHeight / 2;

	healthIndicatorSprite.setPosition((float)x0 + 10, (float)y0 + 7);
	window.draw(healthIndicatorSprite);

	manaIndicatorSprite.setPosition((float)x0 + 10, (float)y0 + 52);
	window.draw(manaIndicatorSprite);

	moneyIndicatorSprite.setPosition((float)x0 + 10, (float)y0 + 97);
	window.draw(moneyIndicatorSprite);

	RectangleShape healthBar;
	healthBar.setOutlineColor(Color::Black);
	healthBar.setOutlineThickness(2);
	Color grey(169, 169, 169);
	Color orange(255, 165, 0);
	
	RectangleShape manaBar;
	manaBar.setOutlineColor(Color::Black);
	manaBar.setOutlineThickness(2);

	healthBar.setPosition(Vector2f((float)x0 + 60, (float)y0 + 10));
	healthBar.setFillColor(grey);
	healthBar.setSize(Vector2f(250, 32));
	window.draw(healthBar);

	manaBar.setPosition(Vector2f((float)x0 + 60, (float)y0 + 55));
	manaBar.setFillColor(grey);
	manaBar.setSize(Vector2f(250, 32));
	window.draw(manaBar);

	if (player.HP > 3 * player.maxHP / 4)
	{
		healthBar.setFillColor(Color::Green);
	}
	else if (player.HP > player.maxHP / 2)
	{
		healthBar.setFillColor(Color::Yellow);
	}
	else if (player.HP > player.maxHP / 4)
	{
		healthBar.setFillColor(orange);
	}
	else
	{
		healthBar.setFillColor(Color::Red);
	}

	healthBar.setSize(Vector2f(250 * (float)player.HP / player.maxHP, 32));
	window.draw(healthBar);

	manaBar.setFillColor(Color::Blue);
	manaBar.setSize(Vector2f(250 * (float)player.MP / player.maxMP, 32));
	window.draw(manaBar);

	ostringstream info1;
	info1 << player.money;
	infoText.setString(info1.str());
	infoText.setPosition((float)x0 + 60, (float)y0 + 92);
	window.draw(infoText);

	ostringstream info2;
	info2 << player.HP;
	infoText.setString(info2.str());
	infoText.setPosition((float)x0 + 60, (float)y0 + 5);
	window.draw(infoText);

	ostringstream info3;
	info3 << player.MP;
	infoText.setString(info3.str());
	infoText.setPosition((float)x0 + 60, (float)y0 + 52);
	window.draw(infoText);
}

void printInfoIfDead(RenderWindow& window, float gameTime, Text infoText, Sprite youDiedSprite, Player player)
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

	string moneyStr = "You earned ";
	ostringstream info;
	info << player.money;
	moneyStr += info.str() + " coins";
	infoText.setString(moneyStr);
	infoText.setPosition((float)x0 + (screenHeight - moneyStr.length()) / 2, (float)y0 + screenHeight / 2 + 130);
	window.draw(infoText);

	infoText.setCharacterSize(40);
}

void smallHealthBar(Entity entity, RenderWindow& window) 
{
	RectangleShape healthBar;
	healthBar.setOutlineColor(Color::Black);
	healthBar.setOutlineThickness(1);
	Color grey(169, 169, 169);
	Color orange(255, 165, 0);

	int x0 = entity.x;
	int y0 = entity.y;

	healthBar.setPosition(Vector2f((float)x0, (float)y0 + entity.h + 5));
	healthBar.setFillColor(grey);
	healthBar.setSize(Vector2f(entity.w, 5));
	window.draw(healthBar);


	if (entity.HP > 3 * entity.maxHP / 4)
	{
		healthBar.setFillColor(Color::Green);
	}
	else if (entity.HP > entity.maxHP / 2)
	{
		healthBar.setFillColor(Color::Yellow);
	}
	else if (entity.HP > entity.maxHP / 4)
	{
		healthBar.setFillColor(orange);
	}
	else
	{
		healthBar.setFillColor(Color::Red);
	}

	healthBar.setSize(Vector2f(entity.w * (float)entity.HP / entity.maxHP, 5));
	window.draw(healthBar);
}

void smallManaBar(Player player, RenderWindow& window)
{
	Color grey(169, 169, 169);

	RectangleShape manaBar;
	manaBar.setOutlineColor(Color::Black);
	manaBar.setOutlineThickness(1);

	int x0 = player.x;
	int y0 = player.y;

	manaBar.setPosition(Vector2f((float)x0, (float)y0 + player.h + 10));
	manaBar.setFillColor(grey);
	manaBar.setSize(Vector2f(player.w, 5));
	window.draw(manaBar);

	manaBar.setFillColor(Color::Blue);
	manaBar.setSize(Vector2f(player.w * (float)player.MP / player.maxMP, 5));
	window.draw(manaBar);
}

#endif