//
//  LambertianMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/20/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include "LambertianMaterial.hpp"
#include "Intersection.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Texture.h"
#include "Utils.hpp"

LambertianMaterial::LambertianMaterial(const Texture *albedo)
    : albedo_(albedo)
{}

Material::Info LambertianMaterial::getScatterRay(const Ray * ray, const Intersection * intersect) const
{
    glm::vec3 target = intersect->getTarget() + Utils::pointInUnitSphere();
    std::unique_ptr<Ray> scatterRay = std::make_unique<Ray>(intersect->getPoint(), target - intersect->getPoint(), ray->getTime());
    glm::vec3 attenuation = albedo_->color(intersect->getUV(), intersect->getPoint());
    float scatterPDF = 0.5f;
    return Material::Info(std::move(scatterRay), attenuation, scatterPDF);
}

std::optional<glm::vec3> LambertianMaterial::getEmittedColor(const glm::vec2 & uv, const glm::vec3 & location) const
{
    return std::nullopt;
}

float LambertianMaterial::getScatterPDF(const Ray * ray, const Ray * scatterRay, const Intersection * intersect) const
{
    float cosAngle = glm::dot(glm::normalize(intersect->getNormal()), glm::normalize(scatterRay->getDirection()));
    if (cosAngle < 0.0f) {
        return 0.0f;
    }
    return cosAngle / float(M_PI);
}
