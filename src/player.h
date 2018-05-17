#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
private:
	int x, y, w, h;
public:
	float speed;

	String file;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String F, int X, int Y, int W, int H) {
		file = F;
		w = W; h = H;
		image.loadFromFile("src\\recources\\images\\" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setPosition(X, Y);
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	
	int getPlayerX() {
		return x;
	}
	int getPlayerY() {
		return y;
	}

	void setPlayerX(int X) {
		 x = X;
	}
	void setPlayerY(int Y) {
		y = Y;
	}
};