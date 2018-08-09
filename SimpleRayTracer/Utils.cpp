//
//  Utils.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Utils.hpp"
#include <cassert>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\norm.hpp>
#include "Intersection.hpp"
#include "HitTestable.h"
#include "Material.h"
#include "RandomNumGen.hpp"
#include "Ray.hpp"

glm::vec3 Utils::pointInUnitSphere()
{
    RandomNumGen rand;
    glm::vec3 point;
    do {
        point = Utils::toNormalSpace(glm::vec3(rand.generate(), rand.generate(), rand.generate()));
    } while (glm::length2(point) >= 1.0f);
    
    return point;
}

glm::vec3 Utils::pointInUnitDisk()
{
    glm::vec3 point;
    do {
        point = Utils::pointInUnitSphere();
        point.z = 0.0f;
    } while (glm::dot(point, point) >= 1.0f);
    return point;
}

// [-1, +1] -> [0, 1]
glm::vec3 Utils::toColorSpace(glm::vec3 point)
{
    return (point + glm::vec3(1.0f, 1.0f, 1.0f)) * glm::vec3(0.5f, 0.5f, 0.5f);
}

// [0, 1] -> [-1, +1]
glm::vec3 Utils::toNormalSpace(glm::vec3 p)
{
    return (p * 2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::vec3 Utils::trace(const Ray &ray, const HitTestable &item, const int &depth)
{
    std::array<float, 2> range = {0.001f, std::numeric_limits<float>::max() };
    Intersection intersect;
    if (item.hit(ray, range, intersect)) {
        // return sphere color
        assert(intersect.getMaterial());
        Ray bounceRay;
        glm::vec3 attenuation;
        if (depth < 50 && intersect.getMaterial()->scatter(ray, intersect, attenuation, bounceRay)) {
            return Utils::trace(bounceRay, item, depth + 1) * attenuation;
        } else {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    } else {
        // return background
        glm::vec3 direction = glm::normalize(ray.getDirection());
        float t = (direction.y + 1.0f) * 0.5f;
        assert(t >= 0.0f && t <= 1.0f);
        glm::vec3 startColor = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 endColor = glm::vec3(0.5f, 0.7f, 1.0f);
        return ((1.0f - t) * startColor) + (t * endColor);
    }
}
// https://en.wikipedia.org/wiki/Schlick%27s_approximation
float Utils::fresnel(const float cosine, const float referactiveIndex)
{
    float r = glm::pow((1 - referactiveIndex)/(1 + referactiveIndex), 2.0f);
    return r + (1 - r) * glm::pow(1 - cosine, 5.0f);
}
