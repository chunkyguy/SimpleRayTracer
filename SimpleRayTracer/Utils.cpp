//
//  Utils.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Utils.hpp"

#include "Intersection.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"

simd::float3 Utils::trace(const Ray &ray, const Sphere &sphere)
{
    Intersection intersect = Utils::hit(ray, sphere);
    if (intersect.isIntersecting) {
        // return sphere color
        simd::float3 normal = simd::normalize(ray.pointAt(intersect.point) - simd::make_float3(0, 0, -1));
        return (normal + simd::make_float3(1.0f, 1.0f, 1.0f)) * simd::make_float3(0.5f, 0.5f, 0.5f);
    }
    
    // return background
    simd::float3 direction = simd::normalize(ray.getDirection());
    float t = (direction.y + 1.0f) * 0.5f;
    simd::float3 startColor = simd::make_float3(1.0f, 1.0f, 1.0f);
    simd::float3 endColor = simd::make_float3(0.5f, 0.7f, 1.0f);
    return ((1.0f - t) * startColor) + (t * endColor);
}

Intersection Utils::hit(const Ray &ray, const Sphere &sphere)
{
    simd::float3 center = ray.getOrigin() - sphere.center;
    simd::float3 direction = ray.getDirection();
    float radius = sphere.radius;
    
    float a = simd::dot(direction, direction);
    float b = 2.0 * simd::dot(center, direction);
    float c = simd::dot(center, center) - (radius * radius);
    float d = (b * b) - (4 * a * c);
    float root = (-b - simd::sqrt(d))/ (2.0 * a);

    return Intersection(d > 0, root);
}
