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
    return float(drand48());
}
