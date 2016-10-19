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
	double noise, cobbleNoise;

	//not using std::srand as it can generate isoplanes, the mersenne twister is a far better choice
	std::mt19937 generator;
	std::uniform_real_distribution<double> distribution(-.9, .9);
	generator.seed(std::random_device{}()); //non deterministic seed
	double randomNumber = distribution(generator); //keeping it down for the noise generator

	double noiseCounter = randomNumber;
	double cobbleCounter = randomNumber;

	int terrainOffset = height / 2;
	int cobbleOffsetMinimum = 5;
	int cobbleOffset = terrainOffset + cobbleOffsetMinimum + (int)(std::abs(randomNumber)*10); //offsetting the cobblestone down (cobbleOffsetMinimum is the minimum distance)

	std::cout << "Starting terrain generation" << std::endl;

	for (int x = 0; x < width; x++)
	{
		//current noise for given x
		noise = perlin.noise(noiseCounter) * 4;
		cobbleNoise = perlin.noise(cobbleCounter) * 4;

		//calculating new offsetts
		terrainOffset += (int)noise;
		cobbleOffset += (int)cobbleNoise;
		//we now make sure the cobbleOffset is always larger then our terrainOffset+cobbleOffsetMinimum
		cobbleOffset > terrainOffset + cobbleOffsetMinimum ? cobbleOffset = cobbleOffset : cobbleOffset = terrainOffset + cobbleOffsetMinimum;

		//getting a new random number and advancing the counter for each layer
		randomNumber = distribution(generator);
		noiseCounter = randomNumber;
		
		randomNumber = distribution(generator);
		cobbleCounter = randomNumber;
		
		//generating the terrain
		for (int y = 0; y < height; y++)
		{
			if (y == terrainOffset)
			{
				map += "0"; //grass on top
			}
			else if (y > terrainOffset && y <= cobbleOffset)
			{
				map += "1"; //dirt
			}
			else if (y > cobbleOffset)
			{
				map += "2"; //cobblestone
			}
			else
			{
				map += "N"; //null is the sky
			}
		}
	}
	return map;
}
