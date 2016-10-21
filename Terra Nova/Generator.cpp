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

	//the noise counters will be functionally equivalent to Time in the Perlin noise generator
	double noiseCounter = randomNumber;
	double cobbleCounter = randomNumber;

	//offsetting the terrain so that it doesn't start on top of the screen
	int terrainOffset;
	height > 60 ? terrainOffset = height / 3 : terrainOffset = height / 2;

	//offsetting the cobblestone in regard to the terrain
	int cobbleOffsetMinimum = 5;
	int cobbleOffset = terrainOffset + cobbleOffsetMinimum + (int)(std::abs(randomNumber)*10); //offsetting the cobblestone down (cobbleOffsetMinimum is the minimum distance)

	//minerals related stuff
	std::uniform_real_distribution<float> distributionFloat(0, 100);
	generator.seed(std::random_device{}()); //non deterministic seed
	float randomFloat = distributionFloat(generator); //keeping it down for the noise generator

	float ironRarity = 7;
	float goldRarity = 2;
	float diamondRarity = .5f;

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
			else if (y > terrainOffset && y == cobbleOffset)
			{
				map += "3"; //dirt - cobblestone transition
			}
			else if (y > terrainOffset && y < cobbleOffset)
			{
				map += "1"; //dirt
			}
			else if (y > cobbleOffset)
			{
				//spawning minerals according to the rarity and the depth
				if (randomFloat <= diamondRarity)
					map += "6";
				else if (randomFloat > diamondRarity && randomFloat <= goldRarity)
					map += "5";
				else if (randomFloat > goldRarity && randomFloat <= ironRarity)
					map += "4";
				else
					map += "2"; //cobblestone

				//getting a new float for the next iteration
				randomFloat = distributionFloat(generator);
			}
			else
			{
				map += "N"; //null is the sky
			}
		}

		//second pass

	}
	return map;
}
