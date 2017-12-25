//
//  Material.h
//  SimpleRayTracer
//
//  Created by Sidharth on 12/18/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Material_h
#define Material_h
#include <simd/simd.h>

class Ray;
class Intersection;

struct Material {
    virtual
    ~Material();
    
    virtual
    bool scatter (const Ray &ray, const Intersection &intersect,
                          simd::float3 &attenuation, Ray &bounce) const = 0;
};

inline
Material::~Material()
{}
#endif /* Material_h */
