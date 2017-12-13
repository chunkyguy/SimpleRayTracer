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
    
    Camera(const simd::float3 &origin, const simd::float3 &lowerLeft,
           const simd::float3 &horizontal, const simd::float3 &vertical);

    Ray getRay(const simd::float2 &uv) const;
    
private:
    simd::float3 _origin;
    simd::float3 _lowerLeft;
    simd::float3 _horizontal;
    simd::float3 _vertical;
};

#endif /* Camera_hpp */
