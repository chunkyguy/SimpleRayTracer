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

bool Sphere::hit(const Ray &ray, const std::array<float, 2> &range, Intersection &intersect) const
{
    simd::float3 center = ray.getOrigin() - _center;
    simd::float3 direction = ray.getDirection();
    
    float a = simd::dot(direction, direction);
    float b = 2.0f * simd::dot(center, direction);
    float c = simd::dot(center, center) - (_radius * _radius);
    float d = (b * b) - (4.0f * a * c);
    
    bool isIntersecting = false;
    float t = 0;
    
    if (d > 0) {
        float root0 = (-b - simd::sqrt(d))/ (a * 2.0f);
        float root1 = (-b + simd::sqrt(d))/ (a * 2.0f);
        if (root0 > range[0] && root0 < range[1]) {
            t = root0;
            isIntersecting = true;
        } else if (root1 > range[0] && root1 < range[1]) {
            t = root1;
            isIntersecting = true;
        }
    }
    
    if (isIntersecting) {
        simd::float3 point = ray.pointAt(t);
        intersect.point = point;
        intersect.distance = t;
        intersect.normal = (point - _center)/_radius;
    }
    
    return isIntersecting;
}
