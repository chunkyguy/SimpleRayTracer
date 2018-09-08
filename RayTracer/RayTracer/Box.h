#pragma once
#include "HitTestable.h"
#include <glm\glm.hpp>

class Material;
class Space;

class Box :
    public HitTestable
{
public:
    Box(const glm::vec3 & min, const glm::vec3 & max, const Material * material);
    ~Box();

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const;

private:
    const glm::vec3 min_;
    const glm::vec3 max_;
    Space *space_;
};

