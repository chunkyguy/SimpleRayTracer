//
//  Utils.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Utils.hpp"
#include <cassert>
#include "Intersection.hpp"
#include "HitTestable.h"
#include "RandomNumGen.hpp"
#include "Ray.hpp"

namespace {
    simd::float3 pointInUnitSphere()
    {
        RandomNumGen rand;
        simd::float3 point;
        do {
            point = Utils::toNormalSpace(simd::make_float3(rand.generate(), rand.generate(), rand.generate()));
        } while (simd::length_squared(point) >= 1.0f);
        
        return point;
    }
}

// [-1, +1] -> [0, 1]
simd::float3 Utils::toColorSpace(simd::float3 point)
{
    return (point + simd::make_float3(1.0f, 1.0f, 1.0f)) * simd::make_float3(0.5f, 0.5f, 0.5f);
}

// [0, 1] -> [-1, +1]
simd::float3 Utils::toNormalSpace(simd::float3 p)
{
    return (p * 2.0) - simd::make_float3(1.0f, 1.0f, 1.0f);
}

simd::float3 Utils::trace(const Ray &ray, const HitTestable &item)
{
    std::array<float, 2> range = {0.001f, MAXFLOAT};
    Intersection intersect;
    if (item.hit(ray, range, intersect)) {
        // return sphere color
        simd::float3 target = intersect.point + intersect.normal + pointInUnitSphere();
        Ray bounceRay(intersect.point, target - intersect.point);
        return Utils::trace(bounceRay, item) * 0.5f;
    } else {
        // return background
        simd::float3 direction = simd::normalize(ray.getDirection());
        float t = (direction.y + 1.0f) * 0.5f;
        assert(t >= 0.0f && t <= 1.0f);
        simd::float3 startColor = simd::make_float3(1.0f, 1.0f, 1.0f);
        simd::float3 endColor = simd::make_float3(0.5f, 0.7f, 1.0f);
        return ((1.0f - t) * startColor) + (t * endColor);
    }
}

