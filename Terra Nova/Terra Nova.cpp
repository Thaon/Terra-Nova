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

	int w = 300;
	int h = 100;

	std::cout << "Enter width in tiles: ";
	std::cin >> w;
	std::cout << std::endl << "Enter height in tiles: ";
	std::cin >> h;
	std::cout << std::endl;

	std::string file = "test";

	std::string map = gen.GenerateMap(w, h);
	plot.GenerateImage(w, h, file, map);

	
	//Perlin perlin;
	//for (double d = 0; d < 10; d += 0.5)
	//{
	//	double noise = perlin.noise(d);
	//	std::cout << noise << std::endl;
	//}
	std::cout << "Done!" << std::endl;
	system("PAUSE");
	return 0;
}

