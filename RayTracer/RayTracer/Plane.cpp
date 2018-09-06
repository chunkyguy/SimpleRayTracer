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

Plane::Plane(const glm::vec2 & min, const glm::vec2 & max, const Edge edge, const float value, const Material * material, const bool flipNormal)
    : min_(min), max_(max), edge_(edge), value_(value), material_(material), flipNormal_(flipNormal)
{}

Plane::~Plane()
{}

std::unique_ptr<Intersection> Plane::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    int edge, aEdge, bEdge;
    switch (edge_) {
    case Edge::X:
        edge = 0;
        aEdge = 1;
        bEdge = 2;
        break;

    case Edge::Y:
        aEdge = 0;
        edge = 1;
        bEdge = 2;
        break;

    case Edge::Z:
        aEdge = 0;
        bEdge = 1;
        edge = 2;
        break;
    }

    return hit(ray, timeRange, edge, aEdge, bEdge);
}

std::unique_ptr<Intersection> Plane::hit(const Ray * ray, const glm::vec2 & timeRange, const int edge, const int aEdge, const int bEdge) const
{
    float t = (value_ - ray->getOrigin()[edge]) / ray->getDirection()[edge];

    if (!contains(t, timeRange)) {
        return std::unique_ptr<Intersection>();
    }

    glm::vec3 point = ray->pointAt(t);
    glm::vec2 aRange = glm::vec2(min_[0], max_[0]);
    glm::vec2 bRange = glm::vec2(min_[1], max_[1]);
    if (!contains(point[aEdge], aRange) || !contains(point[bEdge], bRange)) {
        return std::unique_ptr<Intersection>();
    }

    glm::vec3 normal(0.0f, 0.0f, 0.0f);
    normal[edge] = flipNormal_ ? -1.0f : 1.0f;

    glm::vec2 uv(normalize(point[aEdge], aRange), normalize(point[bEdge], bRange));

    return std::make_unique<Intersection>(t, point, normal, uv, material_);
}

std::unique_ptr<AABB> Plane::boundingBox(const glm::vec2 & timeRange) const
{
    float minValue = value_ - 0.0001f;
    float maxValue = value_ + 0.0001f;

    glm::vec3 min, max;
    switch (edge_) {
    case Edge::X: 
        min = glm::vec3(minValue, min_[0], min_[1]);
        max = glm::vec3(maxValue, max_[0], max_[1]);
        break;

    case Edge::Y:
        min = glm::vec3(min_[0], minValue, min_[1]);
        max = glm::vec3(max_[0], maxValue, max_[1]);
        break;

    case Edge::Z:
        min = glm::vec3(min_[0], min_[1], minValue);
        max = glm::vec3(max_[0], max_[1], maxValue);
        break;
    }

    return std::make_unique<AABB>(min, max);
}
