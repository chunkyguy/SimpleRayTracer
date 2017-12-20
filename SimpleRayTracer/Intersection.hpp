//
//  Intersection.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Intersection_hpp
#define Intersection_hpp
#include <simd/simd.h>

class Material;
class Ray;

class Intersection {
public:
    Intersection();
    Intersection(const float distance, const simd::float3 &point,
                 const simd::float3 &normal, const Material *material);

    simd::float3 getTarget() const;
    simd::float3 getPoint() const;
    float getDistance() const;
    simd::float3 getNormal() const;
    const Material *getMaterial() const;

private:
    float _distance;
    simd::float3 _point;
    simd::float3 _normal;
    const Material *_material;
};

inline
Intersection::Intersection()
: _distance(0), _point(0), _normal(0), _material(nullptr)
{}

inline
Intersection::Intersection(const float distance, const simd::float3 &point,
             const simd::float3 &normal, const Material *material)
: _distance(distance), _point(point), _normal(normal), _material(material)
{}

inline
float Intersection::getDistance() const
{
    return _distance;
}

inline
simd::float3 Intersection::getPoint() const
{
    return _point;
}

inline
simd::float3 Intersection::getNormal() const
{
    return _normal;
}

inline
const Material *Intersection::getMaterial() const
{
    return _material;
}

inline 
simd::float3 Intersection::getTarget() const
{
    return _point + _normal;
}

#endif /* Intersection_hpp */
