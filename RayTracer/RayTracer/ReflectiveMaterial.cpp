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

Material::Info ReflectiveMaterial::getScatterRay(const Ray * ray, const Intersection * intersect) const
{
    glm::vec3 reflect = glm::reflect(glm::normalize((ray->getDirection())), intersect->getNormal());
    std::unique_ptr<Ray> scatterRay;
    if (glm::dot(reflect, intersect->getNormal()) > 0.0f) {
        scatterRay = std::make_unique<Ray>(intersect->getPoint(), reflect + (Utils::pointInUnitSphere() * _fuzziness), ray->getTime());
    }
    return Material::Info(std::move(scatterRay), _albedo, 1.0f);
}

std::optional<glm::vec3> ReflectiveMaterial::getEmittedColor(const glm::vec2 & uv, const glm::vec3 & location) const
{
    return std::nullopt;
}

float ReflectiveMaterial::getScatterPDF(const Ray * ray, const Ray * scatterRay, const Intersection * intersect) const
{
    return 1.0f;
}

