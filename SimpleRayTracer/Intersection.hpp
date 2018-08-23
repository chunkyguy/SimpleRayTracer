//
//  Intersection.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Intersection_hpp
#define Intersection_hpp
#include <glm\glm.hpp>

class Material;
class Ray;

class Intersection {
public:
    Intersection(const float distance, const glm::vec3 &point,
                 const glm::vec3 &normal, const Material *material);

    glm::vec3 getTarget() const;
    glm::vec3 getPoint() const;
    float getDistance() const;
    glm::vec3 getNormal() const;
    const Material *getMaterial() const;

private:
    float _distance;
    glm::vec3 _point;
    glm::vec3 _normal;
    const Material *_material;
};

inline
Intersection::Intersection(
    const float distance, const glm::vec3 &point,
    const glm::vec3 &normal, const Material *material)
    : _distance(distance), _point(point), _normal(normal), _material(material)
{}

inline
float Intersection::getDistance() const
{
    return _distance;
}

inline
glm::vec3 Intersection::getPoint() const
{
    return _point;
}

inline
glm::vec3 Intersection::getNormal() const
{
    return _normal;
}

inline
const Material *Intersection::getMaterial() const
{
    return _material;
}

inline 
glm::vec3 Intersection::getTarget() const
{
    return _point + _normal;
}

#endif /* Intersection_hpp */
