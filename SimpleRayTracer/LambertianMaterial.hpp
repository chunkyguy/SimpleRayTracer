//
//  LambertianMaterial.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/20/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef LambertianMaterial_hpp
#define LambertianMaterial_hpp
#include <simd/simd.h>
#include "Material.h"

class LambertianMaterial : public Material {
public:
    LambertianMaterial(const simd::float3 &albedo);
    
    virtual
    bool scatter(const Ray &ray, const Intersection &intersect, simd::float3 &attenuation, Ray &bounce) const;
    
private:
    simd::float3 _albedo;
};

inline
LambertianMaterial::LambertianMaterial(const simd::float3 &albedo)
: _albedo(albedo)
{}

#endif /* LambertianMaterial_hpp */
