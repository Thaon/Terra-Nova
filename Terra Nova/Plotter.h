#pragma once

#include "Common.h"

class Plotter
{
private:
	std::vector<sf::Image> m_tiles;

public:
	Plotter();
	~Plotter();

	void LoadTile(std::string name);
	void LoadTiles();
	void GenerateImage(int width, int height, std::string filename, std::string map);

	//getters and setters
};

