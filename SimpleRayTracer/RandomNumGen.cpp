//
//  RandomNumGen.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/16/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "RandomNumGen.hpp"

RandomNumGen::RandomNumGen()
{
    _distr = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

float RandomNumGen::generate()
{
    return float(drand48());
}
