//
//  Ray.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/7/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <simd/simd.h>

class Ray {
    simd::float3 _origin;
    simd::float3 _direction;
    
public:
    Ray(const simd::float3 &origin, const simd::float3 &dir);
    simd::float3 getOrigin() const;
    simd::float3 getDirection() const;
    simd::float3 pointAt(float t) const;
};

inline Ray::Ray(const simd::float3 &origin, const simd::float3 &direction)
: _origin(origin), _direction(direction)
{}

inline simd::float3 Ray::getOrigin() const
{
    return _origin;
}

inline simd::float3 Ray::getDirection() const
{
    return _direction;
}

inline simd::float3 Ray::pointAt(float t) const
{
    return _origin + (_direction * t);
}

#endif /* Ray_hpp */
