#pragma once
#include "WLMath.hpp"
#include "HitTestable.h"

class Material;

class MovingSphere : public HitTestable
{
public:
    MovingSphere(
        const glm::vec3 &center0,
        const glm::vec3 &center1,
        const glm::vec2 &timeRange,
        float radius, 
        const Material *material
    );

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 & timeRange) const;

    glm::vec3 getCenter(const float time) const;

private:
 
    const glm::vec3 center0_;
    const glm::vec3 center1_;
    const glm::vec2 timeRange_;
    const float radius_;
    const Material *material_;
};
