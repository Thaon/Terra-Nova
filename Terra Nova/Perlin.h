#pragma once

#include "stdafx.h"
#include "Common.h"

//from: http://blog.kazade.co.uk/2014/05/a-public-domain-c11-1d2d3d-perlin-noise.html

class Perlin {
public:
	Perlin(uint32_t seed = 0);

	double noise(double x) const { return noise(x, 0, 0); }
	double noise(double x, double y) const { return noise(x, y, 0); }
	double noise(double x, double y, double z) const;

private:
	std::array<int, 512> p;
};

class PerlinOctave {
public:
	PerlinOctave(int octaves, uint32_t seed = 0);

	double noise(double x) const { return noise(x, 0, 0); }
	double noise(double x, double y) const { return noise(x, y, 0); }
	double noise(double x, double y, double z) const;

private:
	Perlin perlin_;
	int octaves_;
};