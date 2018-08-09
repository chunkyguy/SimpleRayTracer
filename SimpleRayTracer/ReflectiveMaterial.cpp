//
//  ReflectiveMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/24/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "ReflectiveMaterial.hpp"

#include <algorithm>
#include "Intersection.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

ReflectiveMaterial::ReflectiveMaterial(const glm::vec3 &albedo, const float fuzziness)
: _albedo(albedo), _fuzziness(1.0f)
{
    _fuzziness = glm::clamp(fuzziness, 0.0f, 1.0f);
}

bool ReflectiveMaterial::scatter(const Ray &ray, const Intersection &intersect, glm::vec3 &attenuation, Ray &bounce) const
{
    glm::vec3 reflect = glm::reflect(glm::normalize((ray.getDirection())), intersect.getNormal());
    bounce = Ray(intersect.getPoint(), reflect + (Utils::pointInUnitSphere() * _fuzziness));
    attenuation = _albedo;
    return glm::dot(reflect, intersect.getNormal()) > 0.0f;
}
