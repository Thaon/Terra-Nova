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
	LoadTile("IMG/Grass.png");
	LoadTile("IMG/Dirt.png");
	LoadTile("IMG/Cobblestone.png");
	LoadTile("IMG/GrassBlades.png");
	LoadTile("IMG/Tree.png");
}

void Plotter::GenerateImage(int width, int height, std::string filename, std::string map)
{
	sf::Image image;
	int tileSize = 8;
	int realWidth = width * tileSize;
	int realHeight = height* tileSize;

	image.create(realWidth, realHeight, sf::Color::Blue);

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
					std::cout << randomInt << std::endl;
				}
			}

			//reset random number
			randomInt = distributionInt(generator);
		}
	}

	//darken image
	int darkGradient = 0;
	int threshold = (height * tileSize) / 2;  //we start after the grass line

	for (int x = 0; x < width*tileSize; x++)
	{
		darkGradient = 0;
		for (int y = 0; y < height*tileSize; y++)
		{
			if (y > threshold && darkGradient < 255)
			{
				darkGradient++;
			}
			image.setPixel(x, y, sf::Color(image.getPixel(x,y).r, image.getPixel(x, y).g, image.getPixel(x, y).b, 255) - sf::Color(0, 0, 0, darkGradient));
		}
	}

	//now saving the image
	if (!image.saveToFile(filename + ".png"))
		std::cout << "could not save image" << std::endl;
}
