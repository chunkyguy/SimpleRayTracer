#include "Plane.h"

#include "AABB.h"
#include "Intersection.hpp"
#include "Ray.hpp"

namespace
{
    bool contains(const float v, const glm::vec2 & range)
    {
        return v >= range[0] && v <= range[1];
    }

    float normalize(const float v, const glm::vec2 & range)
    {
        return (v - range[0]) / (range[1] - range[0]);
    }
}

Plane::Plane(const glm::vec2 & min, const glm::vec2 & max, const float z, const Material * material)
    : min_(min), max_(max), z_(z), material_(material)
{}

Plane::~Plane()
{}

std::unique_ptr<Intersection> Plane::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    float t = (z_ - ray->getOrigin().z) / ray->getDirection().z;

    if (!contains(t, timeRange)) {
        return std::unique_ptr<Intersection>();
    }

    glm::vec3 point = ray->pointAt(t);
    glm::vec2 xRange = glm::vec2(min_.x, max_.x);
    glm::vec2 yRange = glm::vec2(min_.y, max_.y);
    if (!contains(point.x, xRange) || !contains(point.y, yRange)) {
        return std::unique_ptr<Intersection>();
    }
    
    return std::make_unique<Intersection>(
        t,
        point,
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec2(normalize(point.x, xRange), normalize(point.y, yRange)),
        material_
    );
}

std::unique_ptr<AABB> Plane::boundingBox(const glm::vec2 & timeRange) const
{
    return std::make_unique<AABB>(glm::vec3(min_, z_ - 0.0001f), glm::vec3(max_, z_ + 0.0001f));
}
