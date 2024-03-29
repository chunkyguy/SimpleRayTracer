#pragma once
#include "WLMath.hpp"

class Ray;

class AABB
{
public:
    AABB(const glm::vec3 &min, const glm::vec3 &max);
    AABB(const AABB * left, const AABB * right);
    ~AABB();

    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

    bool hit(const Ray *ray, glm::vec2 timeRange) const;

private:
    float getTime(const int d, const glm::vec3 & origin, const glm::vec3 & direction, const glm::vec3 & v) const;

    glm::vec3 min_;
    glm::vec3 max_;
};

inline glm::vec3 AABB::getMin() const
{
    return min_;
}

inline glm::vec3 AABB::getMax() const
{
    return max_;
}
