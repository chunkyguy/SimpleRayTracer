//
//  MetalMaterial.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/24/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef MetalMaterial_hpp
#define MetalMaterial_hpp

#include "Material.h"
#include <simd/simd.h>

class MetalMaterial : public Material {
public:
    MetalMaterial(const simd::float3 &albedo);
    
    virtual
    bool scatter(const Ray &ray, const Intersection &intersect, simd::float3 &attenuation, Ray &bounce) const;
    
private:
    simd::float3 _albedo;
};

inline
MetalMaterial::MetalMaterial(const simd::float3 &albedo)
: _albedo(albedo)
{}

#endif /* MetalMaterial_hpp */
