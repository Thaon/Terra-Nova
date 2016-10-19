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

	Perlin perlin;
	double noise;

	//not using std::srand as it can generate isoplanes, the mersenne twister is a far better choice
	std::mt19937 generator;
	std::uniform_real_distribution<double> distribution(-.9, .9);
	generator.seed(std::random_device{}()); //non deterministic seed
	double randomNumber = distribution(generator); //keeping it down for the noise generator

	double noiseCounter = randomNumber;

	int terrainOffset = height / 2;

	std::cout << "Starting terrain generation" << std::endl;

	for (int x = 0; x < width; x++)
	{
		//current noise for given x
		noise = perlin.noise(noiseCounter) * 4;
		terrainOffset += (int)noise; //generating a natural terrain

		//getting a new random number and advancing the counter
		randomNumber = distribution(generator);
		std::cout << randomNumber << std::endl;
		noiseCounter = randomNumber;
		
		for (int y = 0; y < height; y++)
		{
			//generation goes here
			if (y == terrainOffset) //grass on top
			{
				map += "0";
			}
			else if (y > terrainOffset) //terrain bottom
			{
				map += "1";
			}
			else
			{
				map += "N"; //null is the sky
			}
		}
	}
	return map;
}
