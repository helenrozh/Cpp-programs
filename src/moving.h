#include <SFML/Graphics.hpp>
#include <iostream>

#define FramesNum 4
#define StrangeConst1 500000
#define StrangeConst2 50 // velocity scale
#define sqrt2 1.4142135

using namespace std;
using namespace sf;

void Moving(Sprite& sprite, int speed, float time) {
	double CurrentFrame = 0;
	int dx = 0, dy = 0;

	if (Keyboard::isKeyPressed(Keyboard::A))
		dx -= 1;

	if (Keyboard::isKeyPressed(Keyboard::D))
		dx += 1;

	if (Keyboard::isKeyPressed(Keyboard::W))
		dy -= 1;

	if (Keyboard::isKeyPressed(Keyboard::S))
		dy += 1;


	if (dx == 1) {
		if (dy == 1) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 600, 120, 120));
			sprite.move(time * speed * StrangeConst2 / sqrt2, time * speed * StrangeConst2 / sqrt2);
		}
		if (dy == 0) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 240, 120, 120));
			sprite.move(time * speed * StrangeConst2, 0);
		}
		if (dy == -1) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 720, 120, 120));
			sprite.move(time * speed * StrangeConst2, -time * speed * StrangeConst2 / sqrt2);
		}
	}
	if (dx == 0) {
		if (dy == 1) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 0, 120, 120));
			sprite.move(0, time * speed * StrangeConst2);
		}
		if (dy == 0) {
			//оставляем как есть
		}
		if (dy == -1) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 360, 120, 120));
			sprite.move(0, -time * speed * StrangeConst2);
		}
	}
	if (dx == -1) {
		if (dy == 1) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 480, 120, 120));
			sprite.move(-time * speed * StrangeConst2, time * speed * StrangeConst2 / sqrt2);
		}
		if (dy == 0) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 120, 120, 120));
			sprite.move(-time * speed * StrangeConst2, 0);
		}
		if (dy == -1) {
			CurrentFrame += StrangeConst1 * time;
			sprite.setTextureRect(IntRect(120 * ((int)CurrentFrame % 4), 840, 120, 120));
			sprite.move(-time * speed * StrangeConst2, -time * speed * StrangeConst2 / sqrt2);
		}
	}
};