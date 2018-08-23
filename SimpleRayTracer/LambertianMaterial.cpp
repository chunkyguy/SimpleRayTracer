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
#include "Utils.hpp"

std::unique_ptr<Ray> LambertianMaterial::scatter(const Ray *ray, const Intersection * intersect, glm::vec3 & attenuation) const
{
    glm::vec3 target = intersect->getTarget() + Utils::pointInUnitSphere();
    attenuation = _albedo;
    return std::make_unique<Ray>(intersect->getPoint(), target - intersect->getPoint(), ray->getTime());
}
