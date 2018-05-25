#ifndef MENU_H
#define MENU_H

#include "defines.h"
#include "player.h"
#include "map.h"
#include "view.h"
#include "interactions.h"
#include "moving.h"
#include "replay.h"
#include "printinfo.h"
#include "weapon.h"
#include "enemy.h"
#include "mana.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

bool isMenu = true;
float maxGameTimeEnemy = 0;
bool isEnemy = true;

#define playX 100
#define playY 200

void menu(RenderWindow& window, Sprite& menuSprite, Text infoText)
{
	view.setCenter(screenWidth / 2, screenHeight / 2);
	menuSprite.setPosition(0, 0);
	window.draw(menuSprite);
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)		//closes window on x
			window.close();
	}
	infoText.setCharacterSize(40);
	infoText.setString("Play");
	infoText.setPosition(Vector2f(playX, playY));
	window.draw(infoText);

	infoText.setString("Quit");
	infoText.setPosition(Vector2f(playX, playY + 50));
	window.draw(infoText);
	window.display();
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2i pixelPos = Mouse::getPosition(window);  //забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		if ((pos.x > playX) && (pos.y > playY) && (pos.x < playX + 100) && (pos.y < playY + 40))
		{
			isMenu = false;
		}
		if ((pos.x > playX) && (pos.y > playY + 50) && (pos.x < playX + 100) && (pos.y < playY + 50 + 40))
		{
			window.close();
		}
	}
}

struct Sprites
{
	Sprite mapSprite;
	Sprite moneyIndicatorSprite;
	Sprite healthIndicatorSprite;
	Sprite manaIndicatorSprite;
	Sprite youDiedSprite;
};

void loadSprites(Sprites& spr, Sprite mapSprite, Sprite& moneyIndicatorSprite, Sprite& healthIndicatorSprite, Sprite& manaIndicatorSprite, Sprite& youDiedSprite)
{
	spr.mapSprite = mapSprite;
	spr.moneyIndicatorSprite = moneyIndicatorSprite;
	spr.healthIndicatorSprite = healthIndicatorSprite;
	spr.manaIndicatorSprite = manaIndicatorSprite;
	spr.youDiedSprite = youDiedSprite;
}

void game(RenderWindow& window, Player& spider, list<Weapon*>&  weapons, list<Enemy*>&  enemies, Clock& clock, Clock& gameTimeClock, Map& map, Sprites& spr, Text infoText, float gameTime)
{
	float time;

	list<Enemy*>::iterator it = enemies.begin();

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)		//closes window on x
			window.close();
		if (event.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				view.setCenter(screenWidth / 2, screenHeight / 2);
				isMenu = true;
			}
		}
	}

	window.display();
	time = (float)clock.getElapsedTime().asSeconds();
	clock.restart();
	window.setFramerateLimit(60);

	window.setView(view);
	map.drawMap(spr.mapSprite, window);
	window.draw(spider.sprite);

	if (spider.isAlive)
	{
		gameTime = gameTimeClock.getElapsedTime().asSeconds();

		//cout << RAND_MAX << " "; 32767
		if (gameTime - maxGameTimeEnemy > 8)
		{
			isEnemy = true;
			maxGameTimeEnemy = gameTime;
		}
		//cout << isShooting << "\n";
		if (isEnemy)
		{
			isEnemy = false;
			enemies.push_back(new Enemy("bee", rand() % (map.width * tileSize), rand() % (map.height * tileSize), 64, 64, 100));
		}

		moving(spider, time);
		//manaUsage(spider, gameTimeClock, window);


		list<Enemy*>::iterator listEnd = enemies.end();
		for (it = enemies.begin(); it != listEnd;)
		{
			if ((*it)->HP > 0)
			{
				(*it)->shooting(spider, window, time, gameTime);
				interactionWithWeapon(weapons, *it, window, time);
				(*it)->update(time, spider, window, enemies, it);
				it++;
			}
			else
			{
				spider.money += 1;
				delete(*it);
				it = enemies.erase(it);
				//listEnd = enemies.end();
			}

		}

		printInfoIfAlive(spider, window, spr.moneyIndicatorSprite, spr.healthIndicatorSprite, spr.manaIndicatorSprite, infoText);
		smallHealthBar(spider, window);
		smallManaBar(spider, window);
		interactionWithMap(spider, map, gameTime);
		spider.update(gameTime);
		getCoordinatesForView(spider, map);
		shootingPlayer(spider, window, weapons, time, gameTime);

	}
	else
	{
		printInfoIfDead(window, gameTime, infoText, spr.youDiedSprite, spider);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			gameTimeClock.restart();
			gameTime = 0;

			list<Enemy*>::iterator listEnd = enemies.end();
			for (it = enemies.begin(); it != listEnd; it++)
			{
				(*it)->isEnemyShooting = true;
				(*it)->maxGameTimeEnemyWeapon = 0;
			}
			maxGameTimeWeapon = 0;
			isShooting = true;
			spider.manaRestoring = true;
			spider.maxGameTimeHealth = 0;
			spider.maxGameTimeMana = 0;
			spider.healthRestoring = true;
			maxGameTimeSpikes = 0;
			spikeDamage = true;

			replay(spider, map, 2);
		}
	}
}


#endif
