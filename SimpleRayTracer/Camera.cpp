//
//  Camera.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Camera.hpp"
#include "Ray.hpp"

Camera::Camera(const simd::float3 &from, const simd::float3 &at, const simd::float3 &up,
               const float fov, const float aspectRatio)
{
    float angle = fov * M_PI/180.0f;
    float halfHeight = simd::tan(angle/2.0f);
    float halfWidth = halfHeight * aspectRatio;
    
    // camera basis vectors
    simd::float3 w = simd::normalize(from - at);
    simd::float3 u = simd::normalize(simd::cross(up, w));
    simd::float3 v = simd::cross(w, u);
    
    _lowerLeft = from - halfWidth * u - halfHeight * v - w;
    _horizontal = 2.0f * halfWidth * u;
    _vertical = 2.0f * halfHeight * v;
    _origin = from;
}

Ray Camera::getRay(const simd::float2 &uv) const
{
    simd::float3 direction = _lowerLeft + (_horizontal * uv.x) + (_vertical * uv.y) - _origin;
    return Ray(_origin, direction);
}

