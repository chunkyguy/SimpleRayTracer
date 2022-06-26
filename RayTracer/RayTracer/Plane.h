#pragma once
#include "HitTestable.h"
#include "WLMath.hpp"
#include "Edge.h"

class Material;

class Plane :
    public HitTestable
{
public:
    Plane(const glm::vec2 &min, const glm::vec2 &max, const Edge edge, const float value, const Material *material, const float normal);
    ~Plane();

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const;

private:
    std::unique_ptr<Intersection> hit(const Ray * ray, const glm::vec2 & timeRange, const int edge, const int aEdge, const int bEdge) const;

    const Material * material_;
    const glm::vec2 min_;
    const glm::vec2 max_;
    const Edge edge_;
    const float value_;
    const float normal_;
};

