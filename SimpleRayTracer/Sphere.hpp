//
//  Sphere.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <simd/simd.h>

struct Sphere {
    Sphere(const simd::float3 &center, float radius);
    
    simd::float3 center;
    float radius;
};

inline Sphere::Sphere(const simd::float3 &center, float radius)
: center(center), radius(radius)
{}

#endif /* Sphere_hpp */
