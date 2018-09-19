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

RefractiveMaterial::RefractiveMaterial(const float refractiveIndex)
    : _refractiveIndex(refractiveIndex)
{}

Material::Info RefractiveMaterial::getScatterRay(const Ray * ray, const Intersection * intersect) const
{
    glm::vec3 rayDirection = ray->getDirection();
    glm::vec3 reflect = glm::reflect(rayDirection, intersect->getNormal());
    
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
    
    std::unique_ptr<Ray> scatterRay;
    float reflectionProb;
    glm::vec3 refract = glm::refract(ray->getDirection(), outNormal, refractiveIndex);
    if (refract.x == 0.0f && refract.y == 0.0f && refract.z == 0.0f) {
        scatterRay = std::move(std::make_unique<Ray>(intersect->getPoint(), reflect, ray->getTime()));
        reflectionProb = 1.0f;
    } else {
        reflectionProb = Utils::fresnel(cosine, refractiveIndex);
    }
    
    RandomNumGen rGen;
    if (rGen.generate() < reflectionProb) {
        scatterRay = std::move(std::make_unique<Ray>(intersect->getPoint(), reflect, ray->getTime()));
    } else {
        scatterRay = std::move(std::make_unique<Ray>(intersect->getPoint(), refract, ray->getTime()));
    }

    return Material::Info(true, glm::vec3(1.0f), 1.0f);
}

float RefractiveMaterial::getScatterPDF(const Ray * ray, const Ray * scatterRay, const Intersection * intersect) const
{
    return 1.0f;
}
