#include "player.h"
#include "defines.h"
#include "map.h"
#include "view.h"
#include "interactions.h"
#include "moving.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

int main() {
	RenderWindow window(VideoMode(screenWidth, screenHeight), "helenrozh", Style::Default);
	view.reset(FloatRect(0, 0, 800, 600));

	Player spider("spider.png", 200, 200, spiderSize, spiderSize);

	Font font;
	font.loadFromFile("src\\recources\\11813.ttf");
	Text text(L"Монеток:", font, 40);
	text.setColor(Color::Black);
	text.setStyle(Text::Bold);

	Image mapImage;
	mapImage.loadFromFile("src\\recources\\images\\background.png");
	Texture map;
	map.loadFromImage(mapImage);
	Sprite s_map;
	s_map.setTexture(map);

	Clock clock;

	while (window.isOpen()) {
		float time = (float)clock.getElapsedTime().asSeconds();
		clock.restart();
		window.setFramerateLimit(60);

		window.setView(view);
		drawMap(s_map, window);
		window.draw(spider.sprite);

		ostringstream spiderMoneyString;
		spiderMoneyString << spider.money;
		text.setString(L"Монеток:  " + spiderMoneyString.str());
		text.setPosition(view.getCenter().x - screenWidth / 2, view.getCenter().y - screenHeight / 2);
		window.draw(text);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)		//closes window on x
				window.close();
		}

		moving(spider, time);
		interactionWithMap(spider);
		spider.update(time);
		getCoordinatesForView(spider);

		window.display();
	}

	return 0;
}