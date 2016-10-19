#pragma once

#include "Common.h"
#include "Perlin.h"

class Generator
{
private:
	std::string m_map;

public:
	Generator();
	~Generator();

	std::string GenerateMap(int width, int height);

	//getters and setters
};

