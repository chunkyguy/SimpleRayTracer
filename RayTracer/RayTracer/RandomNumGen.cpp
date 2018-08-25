//
//  RandomNumGen.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/16/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "RandomNumGen.hpp"
#include <cstdlib>

float RandomNumGen::generate() const
{
	return rand() / float(RAND_MAX);
}

float RandomNumGen::generate(const glm::vec2 & range) const
{
    return range[0] + (generate() * (range[1] - range[0]));
}
