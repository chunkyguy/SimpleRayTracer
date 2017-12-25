//
//  ReflectiveMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/24/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "ReflectiveMaterial.hpp"

#include <algorithm>
#include "Intersection.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

ReflectiveMaterial::ReflectiveMaterial(const simd::float3 &albedo, const float fuzziness)
: _albedo(albedo), _fuzziness(1.0f)
{
    _fuzziness = simd::clamp(fuzziness, 0.0f, 1.0f);
}

bool ReflectiveMaterial::scatter(const Ray &ray, const Intersection &intersect, simd::float3 &attenuation, Ray &bounce) const
{
    simd::float3 reflect = simd::reflect(simd::normalize((ray.getDirection())), intersect.getNormal());
    bounce = Ray(intersect.getPoint(), reflect + (Utils::pointInUnitSphere() * _fuzziness));
    attenuation = _albedo;
    return simd::dot(reflect, intersect.getNormal()) > 0.0f;
}
