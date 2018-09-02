#pragma once
#include "HitTestable.h"
#include <glm\glm.hpp>

class Material;

class Plane :
    public HitTestable
{
public:
    Plane(const glm::vec2 &min, const glm::vec2 &max, const float z, const Material *material);
    ~Plane();

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const;

private:
    const Material * material_;
    const glm::vec2 min_;
    const glm::vec2 max_;
    const float z_;
};

