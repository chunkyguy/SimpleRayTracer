//
//  Sphere.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//
#define _USE_MATH_DEFINES
#include <cmath>

#include "Sphere.hpp"

#include "AABB.h"
#include "Intersection.hpp"
#include "Material.h"
#include "Ray.hpp"

Sphere::Sphere(const glm::vec3 &center, float radius, const Material *material)
: _center(center), _radius(radius), _material(material)
{}

std::unique_ptr<Intersection> Sphere::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    glm::vec3 center = ray->getOrigin() - _center;
    glm::vec3 direction = ray->getDirection();
    
    float a = glm::dot(direction, direction);
    float b = 2.0f * glm::dot(center, direction);
    float c = glm::dot(center, center) - (_radius * _radius);
    float d = (b * b) - (4.0f * a * c);
    
    if (d > 0) {
        float root0 = (-b - glm::sqrt(d))/ (a * 2.0f);
        float root1 = (-b + glm::sqrt(d))/ (a * 2.0f);
        if (root0 > timeRange[0] && root0 < timeRange[1]) {
            return intersect(ray, root0);
        } else if (root1 > timeRange[0] && root1 < timeRange[1]) {
            return intersect(ray, root1);
        }
    }

    return std::unique_ptr<Intersection>();
}

std::unique_ptr<Intersection> Sphere::intersect(const Ray *ray, const float time) const
{
    glm::vec3 point = ray->pointAt(time);
    glm::vec3 normal = (point - _center) / _radius;
    return std::make_unique<Intersection>(time, point, normal, getSphericalCoords(normal), _material);
}

std::unique_ptr<AABB> Sphere::boundingBox(const glm::vec2 & timeRange) const
{
    return std::make_unique<AABB>(_center - glm::vec3(_radius), _center + glm::vec3(_radius));
}

glm::vec2 Sphere::getSphericalCoords(const glm::vec3 &p) const
{
    float phi = atan2f(p.z, p.x);
    float theta = asinf(p.y);
  
    return glm::vec2(
        1.0f - (phi + M_PI) / (2.0f * M_PI),
        (theta + M_PI_2) / M_PI
    );
}
