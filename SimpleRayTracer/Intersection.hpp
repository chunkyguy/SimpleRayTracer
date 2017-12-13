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
    
    Intersection(bool isIntersecting, float position,
                 const simd::float3 &point, const simd::float3 &normal);
    
    bool isIntersecting;
    float position;
    simd::float3 point;
    simd::float3 normal;
};

inline
Intersection::Intersection(bool isIntersecting, float position,
             const simd::float3 &point, const simd::float3 &normal)
: isIntersecting(isIntersecting), position(position), point(point), normal(normal)
{}

#endif /* Intersection_hpp */
