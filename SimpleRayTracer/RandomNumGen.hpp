//
//  RandomNumGen.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/16/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef RandomNumGen_hpp
#define RandomNumGen_hpp
#include <random>

class RandomNumGen {
public:
    RandomNumGen();
    ~RandomNumGen();

    float generate();
    
private:
    std::random_device _device;
    std::mt19937 *_engine;
    std::uniform_real_distribution<double> _distr;
};

#endif /* RandomNumGen_hpp */
