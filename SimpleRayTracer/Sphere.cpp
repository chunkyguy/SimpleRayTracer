//
//  Sphere.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

Sphere::Sphere(const simd::float3 &center, float radius)
: _center(center), _radius(radius)
{}

Intersection Sphere::hit(const Ray &ray, const std::array<float, 2> &range) const
{
    simd::float3 center = ray.getOrigin() - _center;
    simd::float3 direction = ray.getDirection();
    
    float a = simd::dot(direction, direction);
    float b = 2.0 * simd::dot(center, direction);
    float c = simd::dot(center, center) - (_radius * _radius);
    float d = (b * b) - (4 * a * c);
    
    bool isIntersecting = false;
    float point = 0;
    
    if (d > 0) {
        float root0 = (-b - simd::sqrt(d))/ (2.0 * a);
        float root1 = (-b + simd::sqrt(d))/ (2.0 * a);
        if (root0 > range[0] && root0 < range[1]) {
            point = root0;
            isIntersecting = true;
        } else if (root1 > range[0] && root1 < range[1]) {
            point = root1;
            isIntersecting = true;
        }
    }
    
    simd::float3 position = 0;
    simd::float3 normal = 0;
    if (isIntersecting) {
        position = ray.pointAt(point);
        normal = simd::normalize(position - _center);
    }

    return Intersection(isIntersecting, point, position, normal);
}
