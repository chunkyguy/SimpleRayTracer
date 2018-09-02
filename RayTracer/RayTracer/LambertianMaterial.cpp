//
//  LambertianMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/20/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

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

    return Material::Info(std::move(scatterRay), albedo_->color(intersect->getUV(), intersect->getPoint()));
}

std::optional<glm::vec3> LambertianMaterial::getEmittedColor(const glm::vec2 & uv, const glm::vec3 & location) const
{
    return std::nullopt;
}
