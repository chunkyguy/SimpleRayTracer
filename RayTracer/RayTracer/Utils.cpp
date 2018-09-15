//
//  Utils.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Utils.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\norm.hpp>

#include "Camera.hpp"
#include "Intersection.hpp"
#include "HitTestable.h"
#include "Material.h"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "WLAssert.h"

// private functions
namespace
{
    glm::vec3 getColor(const std::unique_ptr<Ray> ray, const HitTestable *item, const int depth, const int maxDepth);

    glm::vec3 getBackgroundColor(const Ray *ray)
    {
        return glm::vec3(0.0f);
    }

    glm::vec3 getHitColor(const Ray *ray, const HitTestable *item, const Intersection *intersect, const int depth, const int maxDepth)
    {
        // return sphere color
        assert(intersect);
        assert(intersect->getMaterial());

        if (depth >= maxDepth) {
            return glm::vec3(0.0f);
        }

        const Material *material = intersect->getMaterial();
        glm::vec3 color = material->getEmittedColor(intersect->getUV(), intersect->getPoint()).value_or(glm::vec3(0.0f));
        Material::Info scatterRayInfo = material->getScatterRay(ray, intersect);
        if (scatterRayInfo.ray) {
            float f = material->getScatterPDF(ray, scatterRayInfo.ray.get(), intersect) / scatterRayInfo.pdf;
            color += scatterRayInfo.attenuation * getColor(std::move(scatterRayInfo.ray), item, depth + 1, maxDepth) * f;
        }
        return color;
    }

    glm::vec3 getColor(const std::unique_ptr<Ray> ray, const HitTestable *item, const int depth, const int maxDepth)
    {
        glm::vec2 timeRange(0.001f, std::numeric_limits<float>::max());
        std::unique_ptr<Intersection> intersect = std::move(item->hit(ray.get(), timeRange));
        if (!intersect) {
            // return background
            return getBackgroundColor(ray.get());
        }

        return getHitColor(ray.get(), item, intersect.get(), depth, maxDepth);
    }
} // private functions

glm::vec3 Utils::getColor(
    const glm::uvec3 &targetSize,
    const glm::uvec2 point,
    const Camera *camera,
    const HitTestable *space,
    const int maxDepth)
{
    RandomNumGen rand;
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
    for (unsigned int s = 0; s < targetSize.z; ++s) {
        glm::vec2 uv = glm::vec2(
            float(point.x + rand.generate()) / float(targetSize.x),
            float(point.y + rand.generate()) / float(targetSize.y)
        );
        color += ::getColor(std::move(camera->getRay(uv)), space, 0, maxDepth);
    }
    glm::vec3 aggregateColor = color / float(targetSize.z);
    return glm::vec3(glm::sqrt(aggregateColor.x),
        glm::sqrt(aggregateColor.y),
        glm::sqrt(aggregateColor.z)
    );
}

// https://en.wikipedia.org/wiki/Schlick%27s_approximation
float Utils::fresnel(const float cosine, const float referactiveIndex)
{
    float r = glm::pow((1 - referactiveIndex) / (1 + referactiveIndex), 2.0f);
    return r + (1 - r) * glm::pow(1 - cosine, 5.0f);
}

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
    return glm::normalize(point);   
}

glm::vec3 Utils::toColorSpace(glm::vec3 point)
{
    return (point + glm::vec3(1.0f, 1.0f, 1.0f)) * glm::vec3(0.5f, 0.5f, 0.5f);
}

glm::vec3 Utils::toNormalSpace(glm::vec3 p)
{
    return (p * 2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
}
