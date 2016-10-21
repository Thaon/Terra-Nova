#pragma once

//utility
#include "stdafx.h"
#include <iostream>
#include <vector>

//sfml
#include <SFML\Graphics.hpp>


//perlin noise
#include <random>
#include <array>
#include <algorithm>
#include <numeric> 


/**
Features:
FIRST PASS
-----------------------------------------------------------
# random 1st layer height for dirt with grass on top
# random 2nd layer height for cobblestone
	(it can't go below 5 tiles of distance from the ground)

SECOND PASS
-----------------------------------------------------------
random placement of resources:
	-iron = anywhere there is dirt
	-gold = anywhere there is cobblestone
	-diamond = only below 10 units underground

THIRD PASS
-----------------------------------------------------------
random placement of grass and trees
	(trees must be spaced at least 3 tiles apart)
random caves

 # = implemented
*/