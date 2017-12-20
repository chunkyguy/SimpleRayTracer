//
//  LambertianMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/20/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "LambertianMaterial.hpp"
#include "Intersection.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

bool LambertianMaterial::scatter(const Ray &ray, const Intersection &intersect,
                                         simd::float3 &attenuation, Ray &bounce) const
{
    simd::float3 target = intersect.getTarget() + Utils::pointInUnitSphere();
    bounce = Ray(intersect.getPoint(), target - intersect.getPoint());
    attenuation = _albedo;
    return true;
}
