#pragma once
#include "HitTestable.h"
#include <glm\glm.hpp>

class Material;

class Plane :
    public HitTestable
{
public:
    enum class Edge { X, Y, Z };

    Plane *makeYZ(const glm::vec2 & min, const glm::vec2 & max, const float x, const Material * material);
    Plane *makeXZ(const glm::vec2 & min, const glm::vec2 & max, const float y, const Material * material);
    Plane *makeXY(const glm::vec2 & min, const glm::vec2 & max, const float z, const Material * material);

    Plane(const glm::vec2 &min, const glm::vec2 &max, const Edge edge, const float value, const Material *material);
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
};

