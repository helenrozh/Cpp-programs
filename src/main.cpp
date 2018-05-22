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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(screenWidth, screenHeight), "helenrozh", Style::Default);
	view.reset(FloatRect(0, 0, screenWidth, screenHeight));

	Player spider("spider", 200, 200, spiderSize, spiderSize, 100);

	Font font;
	Text infoText("", font, 32);
	font.loadFromFile("src\\recources\\font2.ttf");
	infoText.setColor(Color::Black);
	infoText.setStyle(Text::Bold);

	Map map;
	map.readMap(1);

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

	Clock clock;
	Clock gameTimeClock;
	float gameTime = 0;
	float time = 0;

	while (window.isOpen())
	{
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

			moving(spider, time);
			printInfoIfAlive(spider, window, moneyIndicatorSprite, healthIndicatorSprite, infoText);
			interactionWithMap(spider, map, gameTime);
			spider.update(gameTime);
			getCoordinatesForView(spider, map);
		}
		else
		{
			printInfoIfDead(window, gameTime, infoText, youDiedSprite);

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				replay(spider, map, 1);
			}
		}
	}
	return 0;
}

#endif