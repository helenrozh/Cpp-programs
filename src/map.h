#ifndef MAP_H
#define MAP_H

#include "defines.h"
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Map 
{
public:
	string tile[maxMapHeight];
	int width;
	int height;

	Map() 
	{
		width = 0;
		height = 0;
	}

	void readMap(int mapNum)
	{
		ostringstream mapSub;
		string mapStr;
		mapSub << mapNum;
		mapStr = "src\\recources\\maps\\" + mapSub.str() + ".txt";

		int i = 0;
		string line;
		ifstream mapFile(mapStr);
		if (mapFile.is_open())
		{
			mapFile >> width >> height;
			cout << width << " " << height << "\n";
			getline(mapFile, line);
			while (i < height)
			{
				getline(mapFile, line);
				tile[i] = line;
				//cout << tile[i] << "\n";
				i++;
				/*for (int j = 0; j < width; j++)
				{
					cout << tile[i - 1][j];
				}
				cout << "\n";*/
			}
			mapFile.close();
		}

		else cout << "Unable to open file";
	}

	void drawMap(Sprite mapSprite, RenderWindow& window)
	{
		window.clear(Color::White);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (tile[i][j] == ' ')  mapSprite.setTextureRect(IntRect(0, 0, tileSize, tileSize));
				if (tile[i][j] == 'm')  mapSprite.setTextureRect(IntRect(0, 1 * tileSize, tileSize, tileSize));
				if (tile[i][j] == 's')  mapSprite.setTextureRect(IntRect(0, 2 * tileSize, tileSize, tileSize));
				if (tile[i][j] == 'w')  mapSprite.setTextureRect(IntRect(0, 3 * tileSize + 1, tileSize, tileSize));

				mapSprite.setPosition((float)j * tileSize, (float)i * tileSize);
				window.draw(mapSprite);
			}
		}
	}
};

#endif