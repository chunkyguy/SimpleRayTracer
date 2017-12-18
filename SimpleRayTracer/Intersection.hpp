//
//  Intersection.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Intersection_hpp
#define Intersection_hpp
#include <simd/simd.h>

struct Intersection {
    float distance;
    simd::float3 point;
    simd::float3 normal;
};

#endif /* Intersection_hpp */
