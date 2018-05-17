#include "moving.h"		
#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
	RenderWindow window(VideoMode(screenWidth, screenHeight), "helenrozh", Style::Default);
	view.reset(FloatRect(0, 0, 640, 480));

	Player spider("spider.png", 0, 0, 120, 120);

	Image mapImage;
	mapImage.loadFromFile("src\\recources\\images\\background.png");
	Texture map;
	map.loadFromImage(mapImage);
	Sprite s_map;
	s_map.setTexture(map);

	int speed = 5;
	Clock clock;

	while (window.isOpen()) {
		float time = (float)clock.getElapsedTime().asSeconds();
		clock.restart();
		window.setFramerateLimit(60);

		window.setView(view);
		window.clear(Color::White);
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 64, 64));
				if (TileMap[i][j] == 'w')  s_map.setTextureRect(IntRect(0, 65, 64, 64));

				s_map.setPosition(j * 64, i * 64);
				window.draw(s_map);
			}
		window.draw(spider.sprite);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)		//closes window on x
				window.close();
		}

		Moving(spider, speed, time);
		//cout << "(" << spider.getPlayerX() << " " << spider.getPlayerY() << ")";
		//getCoordinatesForView(spider.getPlayerX(), spider.getPlayerY());

		window.display();
	}

	return 0;
}

