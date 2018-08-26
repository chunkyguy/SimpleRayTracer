#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "HitTestable.h"

class AABB;

/* Bounding volume hierarchy */
class BVH :  public HitTestable
{
public:
    BVH(std::vector<HitTestable *> list, const glm::vec2 &timeRange);
    ~BVH();

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const;

private:

    std::unique_ptr<AABB> boundingBox() const;

    HitTestable * left_;
    HitTestable * right_;
    glm::vec2 timeRange_;
    bool hasChildren_;
};