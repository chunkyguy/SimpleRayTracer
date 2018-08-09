//
//  Sphere.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Material.h"
#include "Ray.hpp"

Sphere::Sphere(const glm::vec3 &center, float radius, const Material *material)
: _center(center), _radius(radius), _material(material)
{}

Sphere::~Sphere()
{
    delete _material;
}

bool Sphere::hit(const Ray &ray, const std::array<float, 2> &range, Intersection &intersect) const
{
    glm::vec3 center = ray.getOrigin() - _center;
    glm::vec3 direction = ray.getDirection();
    
    float a = glm::dot(direction, direction);
    float b = 2.0f * glm::dot(center, direction);
    float c = glm::dot(center, center) - (_radius * _radius);
    float d = (b * b) - (4.0f * a * c);
    
    bool isIntersecting = false;
    float t = 0;
    
    if (d > 0) {
        float root0 = (-b - glm::sqrt(d))/ (a * 2.0f);
        float root1 = (-b + glm::sqrt(d))/ (a * 2.0f);
        if (root0 > range[0] && root0 < range[1]) {
            t = root0;
            isIntersecting = true;
        } else if (root1 > range[0] && root1 < range[1]) {
            t = root1;
            isIntersecting = true;
        }
    }
    
    if (isIntersecting) {
        glm::vec3 point = ray.pointAt(t);
        intersect = Intersection(t, point, (point - _center)/_radius, _material);
    }
    
    return isIntersecting;
}
