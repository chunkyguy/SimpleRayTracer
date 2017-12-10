//
//  Utils.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Utils.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"

simd::float3 Utils::trace(const Ray &ray, const Sphere &sphere)
{
    if (Utils::hit(ray,sphere)) {
        // return sphere color
        return simd::make_float3(1, 0, 0);
    }
    
    // return background
    simd::float3 direction = simd::normalize(ray.getDirection());
    float t = (direction.y + 1.0f) * 0.5f;
    simd::float3 startColor = simd::make_float3(1.0f, 1.0f, 1.0f);
    simd::float3 endColor = simd::make_float3(0.5f, 0.7f, 1.0f);
    return ((1.0f - t) * startColor) + (t * endColor);
}

 bool Utils::hit(const Ray &ray, const Sphere &sphere)
{
    simd::float3 center = ray.getOrigin() - sphere.center;
    simd::float3 direction = ray.getDirection();
    float radius = sphere.radius;
    
    float a = simd::dot(direction, direction);
    float b = 2.0 * simd::dot(center, direction);
    float c = simd::dot(center, center) - (radius * radius);
    float d = (b * b) - (4 * a * c);
    return d > 0;
}
