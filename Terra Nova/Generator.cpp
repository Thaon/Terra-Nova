#include "stdafx.h"
#include "Generator.h"


Generator::Generator()
{
}


Generator::~Generator()
{
}

std::string Generator::GenerateMap(int width, int height)
{
	std::string map = "";

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			//generation goes here
			map += "1";
		}
	}
	return map;
}
