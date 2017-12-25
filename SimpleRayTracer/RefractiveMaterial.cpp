//
//  RefractiveMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/25/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "RefractiveMaterial.hpp"

#include <iostream>

#include "Intersection.hpp"
#include "Ray.hpp"

bool RefractiveMaterial::scatter (const Ray &ray, const Intersection &intersect,
                      simd::float3 &attenuation, Ray &bounce) const
{
    simd::float3 rayDirection = simd::normalize((ray.getDirection()));
    simd::float3 reflect = simd::reflect(rayDirection, intersect.getNormal());
    attenuation = simd::make_float3(1.0f, 1.0f, 1.0f);

    simd::float3 outNormal;
    float refractiveIndex;
    if (simd::dot(rayDirection, intersect.getNormal()) > 0.0f) {
        outNormal = intersect.getNormal() * -1.0f;
        refractiveIndex = _refractiveIndex;
    } else {
        outNormal = intersect.getNormal();
        refractiveIndex = 1.0f/_refractiveIndex;
    }
    
    simd::float3 refract = simd::refract(ray.getDirection(), outNormal, refractiveIndex);
    if (refract.x == 0.0f && refract.y == 0.0f && refract.z == 0.0f) {
        bounce = Ray(intersect.getPoint(), reflect);
        return false;
    } else {
        bounce = Ray(intersect.getPoint(), refract);
        return true;
    }
}
