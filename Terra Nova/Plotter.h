#pragma once

#include "Common.h"

typedef std::vector<sf::Image> ImageVector;


class Plotter
{
private:
	ImageVector m_tiles;

public:
	Plotter();
	~Plotter();

	void LoadTile(std::string name);
	void LoadTiles();
	void GenerateImage(int width, int height, std::string filename, std::string map);

	//getters and setters
};

