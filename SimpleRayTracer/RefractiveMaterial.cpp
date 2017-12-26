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
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

bool RefractiveMaterial::scatter (const Ray &ray, const Intersection &intersect,
                      simd::float3 &attenuation, Ray &bounce) const
{
    simd::float3 rayDirection = ray.getDirection();
    simd::float3 reflect = simd::reflect(rayDirection, intersect.getNormal());
    attenuation = simd::make_float3(1.0f, 1.0f, 1.0f);

    simd::float3 outNormal;
    float refractiveIndex;
    float cosine;
    float dotProduct = simd::dot(rayDirection, intersect.getNormal());
    if (dotProduct > 0.0f) {
        outNormal = intersect.getNormal() * -1.0f;
        refractiveIndex = _refractiveIndex;
        cosine = (dotProduct/simd::length(ray.getDirection())) * refractiveIndex;
    } else {
        outNormal = intersect.getNormal();
        refractiveIndex = 1.0f/_refractiveIndex;
        cosine = (dotProduct/simd::length(ray.getDirection())) * -1.0f;
    }
    
    float reflectionProb;
    simd::float3 refract = simd::refract(ray.getDirection(), outNormal, refractiveIndex);
    if (refract.x == 0.0f && refract.y == 0.0f && refract.z == 0.0f) {
        bounce = Ray(intersect.getPoint(), reflect);
        reflectionProb = 1.0f;
    } else {
        reflectionProb = Utils::fresnel(cosine, refractiveIndex);
    }
    
    RandomNumGen rGen;
    if (rGen.generate() < reflectionProb) {
        bounce = Ray(intersect.getPoint(), reflect);
    } else {
        bounce = Ray(intersect.getPoint(), refract);
    }
    
    return true;
}
