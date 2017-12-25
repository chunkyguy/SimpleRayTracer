//
//  ReflectiveMaterial.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/24/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef MetalMaterial_hpp
#define MetalMaterial_hpp

#include "Material.h"
#include <simd/simd.h>

class ReflectiveMaterial : public Material {
public:
    ReflectiveMaterial(const simd::float3 &albedo, const float fuzziness);
    
    virtual
    bool scatter(const Ray &ray, const Intersection &intersect, simd::float3 &attenuation, Ray &bounce) const;
    
private:
    simd::float3 _albedo;
    float _fuzziness;
};

#endif /* MetalMaterial_hpp */
