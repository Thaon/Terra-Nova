#include "stdafx.h"
#include "Plotter.h"


Plotter::Plotter()
{
	m_tiles = std::vector<sf::Image>();
}


Plotter::~Plotter()
{
}

void Plotter::LoadTile(std::string name)
{
	sf::Image tile = sf::Image();
	if (!tile.loadFromFile(name))
	{
		std::cout << "could not load image: " << name << std::endl;
		system("PAUSE");
		return;
	}
	m_tiles.push_back(tile);
}

void Plotter::LoadTiles()
{
	//we load all our images here manually
	LoadTile("IMG/Grass.png");				//0
	LoadTile("IMG/Dirt.png");				//1
	LoadTile("IMG/Cobblestone.png");		//2
	LoadTile("IMG/GrassBlades.png");		//3
	LoadTile("IMG/Tree.png");				//4
	LoadTile("IMG/Dirt-Cobblestone.png");	//5
	LoadTile("IMG/IronOre.png");			//6
	LoadTile("IMG/GoldOre.png");			//7
	LoadTile("IMG/DiamondOre.png");			//8
}

void Plotter::GenerateImage(int width, int height, std::string filename, std::string map)
{
	sf::Image image;
	int tileSize = 8;
	int realWidth = width * tileSize;
	int realHeight = height* tileSize;

	image.create(realWidth, realHeight, sf::Color(162, 195, 249));

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			switch (map[y+(height*x)]) //offsetting the y to read the whole map
			{
			case '0':
				image.copy(m_tiles[0], x*tileSize, y*tileSize); //grass
				break;

			case '1':
				image.copy(m_tiles[1], x*tileSize, y*tileSize); //dirt
				break;
			
			case '2':
				image.copy(m_tiles[2], x*tileSize, y*tileSize); //cobblestone
				break;

			case '3':
				image.copy(m_tiles[5], x*tileSize, y*tileSize); //cobblestone
				break;

			case '4':
				image.copy(m_tiles[6], x*tileSize, y*tileSize); //iron ore
				break;

			case '5':
				image.copy(m_tiles[7], x*tileSize, y*tileSize); //gold ore
				break;

			case '6':
				image.copy(m_tiles[8], x*tileSize, y*tileSize); //diamond ore
				break;

			default:
				break;
			}
		}
	}

	//third pass here as it is purely decorative

	std::mt19937 generator;
	std::uniform_int_distribution<int> distributionInt(1, 10);
	int randomInt = distributionInt(generator);

	int grassChance = 4; //out of 10
	int treeChance = 2; //out of 10

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			//place grass
			if (map[y + (height*x)] == '0')
			{
				if (randomInt <= grassChance)
					image.copy(m_tiles[3], x*tileSize, (y - 1)*tileSize, sf::IntRect(0, 0, 8, 8), true);
				//place trees
				if (x > 2 && x < width*tileSize && randomInt <= treeChance)
				{
					image.copy(m_tiles[4], (x - 1)*tileSize, (y - 3)*tileSize, sf::IntRect(0, 0, 24, 24), true);
				}
			}

			//reset random number
			randomInt = distributionInt(generator);
		}
	}

	//darken image
	float darkGradient = 0;
	int threshold = (height * tileSize) / 2;  //we start after the grass line

	for (int x = 0; x < width*tileSize; x++)
	{
		darkGradient = 0;
		for (int y = 0; y < height*tileSize; y++)
		{
			if (y > threshold && darkGradient < 240)
			{
				darkGradient+=.7F;
			}
			image.setPixel(x, y, sf::Color(image.getPixel(x,y).r, image.getPixel(x, y).g, image.getPixel(x, y).b, 255) - sf::Color(0, 0, 0, darkGradient));
		}
	}

	//now saving the image
	if (!image.saveToFile(filename + ".png"))
		std::cout << "could not save image" << std::endl;
}
