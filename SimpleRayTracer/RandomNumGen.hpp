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
    float generate();
    
private:
    
    std::default_random_engine _randGen;
    std::uniform_real_distribution<float> _distr;
};

#endif /* RandomNumGen_hpp */
