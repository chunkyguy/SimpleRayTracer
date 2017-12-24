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
class HitTestable;

struct Utils {
    
    static
    simd::float3 pointInUnitSphere();

    static
    simd::float3 toColorSpace(simd::float3 point);

    static
    simd::float3 toNormalSpace(simd::float3 p);

    static
    simd::float3 trace(const Ray &ray, const HitTestable &item, const int &depth);    
};

#endif /* Utils_hpp */
