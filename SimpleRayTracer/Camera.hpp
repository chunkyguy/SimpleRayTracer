//
//  Camera.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp
#include <simd/simd.h>

class Ray;

class Camera {
public:
    
    Camera(const simd::float3 &from, const simd::float3 &at, const simd::float3 &up,
           const float fov, const float aspectRatio, const float aperture, const float focalDistance);

    Ray getRay(const simd::float2 &uv) const;
    
private:
    
    simd::float3 _origin;
    simd::float3 _lowerLeft;
    simd::float3 _horizontal;
    simd::float3 _vertical;
    simd::float3x3 _uvw;
    float _apperture;
};

#endif /* Camera_hpp */
