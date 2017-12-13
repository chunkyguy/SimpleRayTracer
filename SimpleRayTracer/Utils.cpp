//
//  Utils.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Utils.hpp"

#include "Intersection.hpp"
#include "HitTestable.h"
#include "Ray.hpp"

simd::float3 Utils::trace(const Ray &ray, const HitTestable &item)
{
    std::array<float, 2> range = {0.0f, MAXFLOAT};
    Intersection intersect = item.hit(ray, range);
    if (intersect.isIntersecting) {
        // return sphere color
        return (intersect.normal + simd::make_float3(1.0f, 1.0f, 1.0f)) * simd::make_float3(0.5f, 0.5f, 0.5f);
    }
    
    // return background
    simd::float3 direction = simd::normalize(ray.getDirection());
    float t = (direction.y + 1.0f) * 0.5f;
    simd::float3 startColor = simd::make_float3(1.0f, 1.0f, 1.0f);
    simd::float3 endColor = simd::make_float3(0.5f, 0.7f, 1.0f);
    return ((1.0f - t) * startColor) + (t * endColor);
}
