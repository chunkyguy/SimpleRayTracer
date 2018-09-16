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
#include "Scene.h"
#include "WLAssert.h"

using namespace glm;

// private functions
namespace
{
    vec3 getColor(const std::unique_ptr<Ray> ray, const Scene *scene, const int depth, const int maxDepth);

    vec3 getHitColor(const Ray *ray, const Scene *scene, const Intersection *intersect, const int depth, const int maxDepth)
    {
        // return hit color
        assert(intersect);
        assert(intersect->getMaterial());

        const Material *material = intersect->getMaterial();
        vec3 emittedColor = material->getEmittedColor(
            intersect->getUV(),
            intersect->getPoint()
        ).value_or(vec3(0.0f, 0.0f, 0.0f));

        if (depth >= maxDepth) {
            // stop bouncing
            return emittedColor;
        }

        Material::Info scatterRayInfo = material->getScatterRay(ray, intersect);
        if (!scatterRayInfo.canScatter) {
            // no bounce
            return emittedColor;
        }

        vec3 lightDir = scene->getRandomLightOrigin() - intersect->getPoint();
        vec3 nLightDir = glm::normalize(lightDir);
        float lightAngle = glm::dot(nLightDir, intersect->getNormal());
        if ( lightAngle < 0.0f) {
            // not facing light
            return emittedColor;
        }

        float lightCosine = fabsf(nLightDir.y);
        if (lightCosine < 0.00001f) {
            // on the edge
            return emittedColor;
        }

        float pdf = length2(lightDir) / (lightCosine * scene->getLightArea());
        std::unique_ptr<Ray> scatterRay = std::make_unique<Ray>(intersect->getPoint(), lightDir, intersect->getTime());
        glm::vec3 hitColor = scatterRayInfo.attenuation;
        float materialPDF = material->getScatterPDF(ray, scatterRay.get(), intersect);       
        return emittedColor + hitColor * materialPDF / pdf * getColor(std::move(scatterRay), scene, depth + 1, maxDepth);
    }

    glm::vec3 getColor(const std::unique_ptr<Ray> ray, const Scene *scene, const int depth, const int maxDepth)
    {
        const HitTestable *space = scene->getSpace();
        glm::vec2 timeRange(0.001f, std::numeric_limits<float>::max());
        std::unique_ptr<Intersection> intersect = std::move(space->hit(ray.get(), timeRange));
        if (!intersect) {
            // return background
            return glm::vec3(0.0f);
        }

        return getHitColor(ray.get(), scene, intersect.get(), depth, maxDepth);
    }
} // private functions

glm::vec3 Utils::getColor(
    const glm::uvec3 &targetSize,
    const glm::uvec2 point,
    const Scene *scene,
    const int maxDepth)
{
    const Camera *camera = scene->getCamera();
    RandomNumGen rand;
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
    for (unsigned int s = 0; s < targetSize.z; ++s) {
        glm::vec2 uv = glm::vec2(
            float(point.x + rand.generate()) / float(targetSize.x),
            float(point.y + rand.generate()) / float(targetSize.y)
        );
        color += ::getColor(std::move(camera->getRay(uv)), scene, 0, maxDepth);
    }
    glm::vec3 aggregateColor = color / float(targetSize.z);
    return glm::vec3(
        glm::sqrt(aggregateColor.x),
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
