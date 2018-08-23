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

std::unique_ptr<Intersection> Sphere::hit(const Ray *ray, const std::array<float, 2>& range) const
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
        if (root0 > range[0] && root0 < range[1]) {
            glm::vec3 point = ray->pointAt(root0);
            return std::make_unique<Intersection>(root0, point, (point - _center) / _radius, _material);
        } else if (root1 > range[0] && root1 < range[1]) {
            glm::vec3 point = ray->pointAt(root1);
            return std::make_unique<Intersection>(root1, point, (point - _center) / _radius, _material);
        }
    }

    return std::unique_ptr<Intersection>();
}
