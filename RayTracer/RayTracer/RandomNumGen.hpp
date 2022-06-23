//
//  RandomNumGen.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/16/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef RandomNumGen_hpp
#define RandomNumGen_hpp
#include "WLMath.hpp"

class RandomNumGen {
public:
    float generate() const ;
    float generate(const glm::vec2 &range) const;
    
private:
};

#endif /* RandomNumGen_hpp */
