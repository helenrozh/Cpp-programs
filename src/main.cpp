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
#include "menu.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list> 
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

//float maxGameTimeEnemy = 0;
//bool isEnemy = true;

int main()
{
	RenderWindow window(VideoMode(screenWidth, screenHeight), "helenrozh", Style::Fullscreen);
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

	Texture menuTexture;
	Sprite menuSprite;
	menuTexture.loadFromFile("src\\recources\\images\\menu.png");
	menuSprite.setTexture(menuTexture);

	Clock clock;
	Clock gameTimeClock;

	list<Weapon*>  weapons;
	list<Enemy*>  enemies;

	Sprites spr;
	loadSprites(spr, mapSprite, moneyIndicatorSprite, healthIndicatorSprite, manaIndicatorSprite, youDiedSprite);
	//enemies.push_back(new Enemy("bee", 1000, 1000, 64, 64, 100));

	float gameTime = 0;

	while (window.isOpen())
	{
		if (isMenu)
		{
			menu(window, menuSprite, infoText);
		}
		else
		{
			game(window, spider, weapons, enemies, clock, gameTimeClock, map, spr, infoText, gameTime);
		}
	}
	return 0;
}

#endif