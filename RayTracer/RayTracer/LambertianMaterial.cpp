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

std::unique_ptr<Ray> LambertianMaterial::scatter(const Ray *ray, const Intersection * intersect, glm::vec3 & attenuation) const
{
    glm::vec3 target = intersect->getTarget() + Utils::pointInUnitSphere();
    attenuation = albedo_->color(intersect->getUV(), intersect->getPoint());
    return std::make_unique<Ray>(intersect->getPoint(), target - intersect->getPoint(), ray->getTime());
}
