//
//  RefractiveMaterial.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/25/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "RefractiveMaterial.hpp"

#include <iostream>

#include "Intersection.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

std::unique_ptr<Ray> RefractiveMaterial::scatter(const Ray *ray, const Intersection * intersect, glm::vec3 & attenuation) const
{
    glm::vec3 rayDirection = ray->getDirection();
    glm::vec3 reflect = glm::reflect(rayDirection, intersect->getNormal());
    attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 outNormal;
    float refractiveIndex;
    float cosine;
    float dotProduct = glm::dot(rayDirection, intersect->getNormal());
    if (dotProduct > 0.0f) {
        outNormal = intersect->getNormal() * -1.0f;
        refractiveIndex = _refractiveIndex;
        cosine = (dotProduct/glm::length(ray->getDirection())) * refractiveIndex;
    } else {
        outNormal = intersect->getNormal();
        refractiveIndex = 1.0f/_refractiveIndex;
        cosine = (dotProduct/glm::length(ray->getDirection())) * -1.0f;
    }
    
    std::unique_ptr<Ray> bounce;
    float reflectionProb;
    glm::vec3 refract = glm::refract(ray->getDirection(), outNormal, refractiveIndex);
    if (refract.x == 0.0f && refract.y == 0.0f && refract.z == 0.0f) {
        bounce = std::move(std::make_unique<Ray>(intersect->getPoint(), reflect, ray->getTime()));
        reflectionProb = 1.0f;
    } else {
        reflectionProb = Utils::fresnel(cosine, refractiveIndex);
    }
    
    RandomNumGen rGen;
    if (rGen.generate() < reflectionProb) {
        bounce = std::move(std::make_unique<Ray>(intersect->getPoint(), reflect, ray->getTime()));
    } else {
        bounce = std::move(std::make_unique<Ray>(intersect->getPoint(), refract, ray->getTime()));
    }
    
    return bounce;
}
