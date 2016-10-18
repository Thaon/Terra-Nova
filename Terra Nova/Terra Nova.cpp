// Terra Nova.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "Plotter.h"

int main()
{
	Generator gen = Generator();
	Plotter plot = Plotter();

	plot.LoadTiles();

	int w = 8;
	int h = 3;
	std::string file = "test";

	std::string map = gen.GenerateMap(w, h);
	plot.GenerateImage(w, h, file, map);

	return 0;
}

