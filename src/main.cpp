#ifndef MAIN_CPP
#define MAIN_CPP

#include "player.h"
#include "defines.h"
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
#include <list> 
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

float maxGameTimeEnemy = 0;
bool isEnemy = true;

int main()
{
	RenderWindow window(VideoMode(screenWidth, screenHeight), "helenrozh", Style::Default);
	view.reset(FloatRect(0, 0, screenWidth, screenHeight));

	Player spider("spider", 500, 500, spiderSize, spiderSize, 100, 100);

	Font font;
	Text infoText("", font, 32);
	font.loadFromFile("src\\recources\\font2.ttf");
	infoText.setColor(Color::Black);
	infoText.setStyle(Text::Bold);

	Map map;
	map.readMap(2);

	Texture mapTexture;
	Sprite mapSprite;
	mapTexture.loadFromFile("src\\recources\\images\\background.png");
	mapSprite.setTexture(mapTexture);

	Texture youDiedTexture;
	Sprite  youDiedSprite;
	youDiedTexture.loadFromFile("src\\recources\\images\\youdied.png");
	youDiedSprite.setTexture(youDiedTexture);

	Texture moneyIndicatorTexture;
	Sprite moneyIndicatorSprite;
	moneyIndicatorTexture.loadFromFile("src\\recources\\images\\money.png");
	moneyIndicatorSprite.setTexture(moneyIndicatorTexture);

	Texture healthIndicatorTexture;
	Sprite healthIndicatorSprite;
	healthIndicatorTexture.loadFromFile("src\\recources\\images\\health.png");
	healthIndicatorSprite.setTexture(healthIndicatorTexture);

	Texture manaIndicatorTexture;
	Sprite manaIndicatorSprite;
	manaIndicatorTexture.loadFromFile("src\\recources\\images\\mana.png");
	manaIndicatorSprite.setTexture(manaIndicatorTexture);

	Clock clock;
	Clock gameTimeClock;
	float gameTime = 0;
	float time = 0;

	list<Weapon*>  weapons;
	list<Enemy*>  enemies;

	//enemies.push_back(new Enemy("bee", 1000, 1000, 64, 64, 100));

	while (window.isOpen())
	{
		list<Enemy*>::iterator it = enemies.begin();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)		//closes window on x
				window.close();
		}

		window.display();
		time = (float)clock.getElapsedTime().asSeconds();
		clock.restart();
		window.setFramerateLimit(60);

		window.setView(view);
		map.drawMap(mapSprite, window);
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
					delete(*it);
					it = enemies.erase(it);
					//listEnd = enemies.end();
				}

			}

			printInfoIfAlive(spider, window, moneyIndicatorSprite, healthIndicatorSprite, manaIndicatorSprite, infoText);
			smallHealthBar(spider, window);
			smallManaBar(spider, window);
			interactionWithMap(spider, map, gameTime);
			spider.update(gameTime);
			getCoordinatesForView(spider, map);
			shootingPlayer(spider, window, weapons, time, gameTime);

		}
		else
		{
			printInfoIfDead(window, gameTime, infoText, youDiedSprite);

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
	return 0;
}

#endif