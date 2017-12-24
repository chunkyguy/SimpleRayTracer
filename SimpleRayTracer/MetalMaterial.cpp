//
//  MetalMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/24/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "MetalMaterial.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

bool MetalMaterial::scatter(const Ray &ray, const Intersection &intersect, simd::float3 &attenuation, Ray &bounce) const
{
    simd::float3 reflect = simd::reflect(simd::normalize((ray.getDirection())), intersect.getNormal());
    bounce = Ray(intersect.getPoint(), reflect);
    attenuation = _albedo;
    return simd::dot(reflect, intersect.getNormal()) > 0.0f;
}
