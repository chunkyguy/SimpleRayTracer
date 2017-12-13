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
#include "HitTestable.h"

class Sphere: public HitTestable {
public:
    Sphere(const simd::float3 &center, float radius);
    virtual Intersection hit(const Ray &ray, const std::array<float, 2> &range) const;

private:
    simd::float3 _center;
    float _radius;
};

#endif /* Sphere_hpp */
