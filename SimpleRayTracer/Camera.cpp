//
//  Camera.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Camera.hpp"
#include "Ray.hpp"

Camera::Camera(const simd::float3 &origin, const simd::float3 &lowerLeft,
       const simd::float3 &horizontal, const simd::float3 &vertical)
: _origin(origin), _lowerLeft(lowerLeft), _horizontal(horizontal), _vertical(vertical)
{}

Ray Camera::getRay(const simd::float2 &uv) const
{
    simd::float3 direction = _lowerLeft + _horizontal * uv.x + _vertical * uv.y - _origin;
    return Ray(_origin, direction);
}

