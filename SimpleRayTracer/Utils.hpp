//
//  Utils.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <simd/simd.h>

class Ray;
class Sphere;

struct Utils {
    static simd::float3 trace(const Ray &ray, const Sphere &sphere);
    static bool hit(const Ray &ray, const Sphere &sphere);
};

#endif /* Utils_hpp */
