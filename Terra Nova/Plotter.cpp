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
}

void Plotter::GenerateImage(int width, int height, std::string filename, std::string map)
{
	sf::Image image;
	int tileSize = 8;
	int realWidth = width * tileSize;
	int realHeight = height* tileSize;

	image.create(realWidth, realHeight, sf::Color::Black);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			switch (map[x])
			{
			case '1':
				image.copy(m_tiles[0], x*tileSize, y*tileSize);
				break;
			}
		}
	}
	//now saving the image
	if (!image.saveToFile(filename + ".png"))
		std::cout << "could not save image" << std::endl;
	system("PAUSE");
}
