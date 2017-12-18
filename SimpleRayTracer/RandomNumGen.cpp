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
    _engine = new std::mt19937(_device());
    _distr = std::uniform_real_distribution<double>(0.0f, 1.0f);
}

RandomNumGen::~RandomNumGen()
{
    delete _engine;
}

float RandomNumGen::generate()
{
    return float(_distr(*_engine));
}
