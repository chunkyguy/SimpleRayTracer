//
//  RandomNumGen.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/16/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "RandomNumGen.hpp"
#include <cstdlib>

float RandomNumGen::generate()
{
	return rand() / float(RAND_MAX);
}

float RandomNumGen::generate(const float min, const float max)
{
    return min + (generate() * (max - min));
}
