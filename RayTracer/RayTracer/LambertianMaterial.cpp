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

#include "CoordinateSystem.h"
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
    CoordinateSystem cs{ intersect->getNormal() };
    glm::vec3 randomAngle = Utils::randomCosineDirection();
    glm::vec3 direction = cs.convert(randomAngle);
    std::unique_ptr<Ray> scatterRay = std::make_unique<Ray>(intersect->getPoint(), direction, ray->getTime());
    glm::vec3 attenuation = albedo_->color(intersect->getUV(), intersect->getPoint());
    
    float scatterPDF = glm::dot(cs.getW(), scatterRay->getDirection()) / static_cast<float>(M_PI);
    
    return Material::Info(true, attenuation, scatterPDF);
}

float LambertianMaterial::getScatterPDF(const Ray * ray, const Ray * scatterRay, const Intersection * intersect) const
{
    float cosAngle = glm::dot(glm::normalize(intersect->getNormal()), glm::normalize(scatterRay->getDirection()));
    if (cosAngle < 0.0f) {
        return 0.0f;
    }
    return cosAngle / float(M_PI);
}
