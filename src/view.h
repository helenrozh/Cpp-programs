//I suppose thate map is bigger than screen size

#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;

#define screenWidth 800
#define screenHeight 600
#define HalfSprite 60

View view;

void getCoordinatesForView(int x, int y) { 
	int cameraX = x;
	int cameraY = y;
	if (x < screenWidth / 2 - 2 * HalfSprite)
		cameraX = screenWidth / 2 - 2 * HalfSprite;
	if (y < screenHeight / 2 - 2 * HalfSprite)
		cameraY = screenHeight / 2 - 2 * HalfSprite;
	if (x > WIDTH_MAP * 64 - screenWidth / 2)
		cameraX = WIDTH_MAP * 64 - screenWidth / 2;
	if (y > HEIGHT_MAP * 64 - screenHeight / 2)
		cameraY = HEIGHT_MAP * 64 - screenHeight / 2;

	view.setCenter(cameraX + HalfSprite, cameraY + HalfSprite);
}