#include "moving.h"			//движение персонажа

int main()
{
	RenderWindow window(VideoMode(800, 600), "helenrozh", Style::Default);

	Image spider;
	spider.loadFromFile("src\\recources\\spider.png");

	Texture texture;
	texture.loadFromImage(spider);

	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 120, 120));
	sprite.setPosition(50, 50);

	int speed = 5;
	Clock clock;

	while (window.isOpen()) {
		float time = (float)clock.getElapsedTime().asSeconds();
		clock.restart();
		window.setFramerateLimit(60);

		window.clear(Color::White);
		window.draw(sprite);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)		//closes window on x
				window.close();
		}

		Moving(sprite, speed, time);

		window.display();
	}

	return 0;
}

