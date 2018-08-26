#include "AABB.h"
#include <algorithm>
#include "Ray.hpp"

AABB::AABB(const AABB *left, const AABB *right)
{
    glm::vec3 lMin = left->getMin();
    glm::vec3 rMin = right->getMin();
    glm::vec3 lMax = left->getMax();
    glm::vec3 rMax = right->getMax();

    min_ = glm::vec3(std::min(lMin.x, rMin.x), std::min(lMin.y, rMin.y), std::min(lMin.z, rMin.z));
    max_ = glm::vec3(std::max(lMax.x, rMax.x), std::max(lMax.y, rMax.y), std::max(lMax.z, rMax.z));
}

AABB::AABB(const glm::vec3 & min, const glm::vec3 & max)
    : min_(min), max_(max)
{}

AABB::~AABB()
{}

bool AABB::hit(const Ray *ray, glm::vec2 timeRange) const
{
    const glm::vec3 rayOrigin = ray->getOrigin();
    const glm::vec3 rayDirection = ray->getDirection();

    for (int d = 0; d < 3; ++d) {
        // get time where ray hits the min plane
        float tMin = getTime(d, rayOrigin, rayDirection, min_);
        
        // get time where ray hits the max plane
        float tMax = getTime(d, rayOrigin, rayDirection, max_);

        // ray could be coming from any direction, get the absolute min and max values
        std::pair<float, float> t = std::minmax(tMin, tMax);

        // get the shortest time range
        glm::vec2 newTimeRange = {
            std::max(t.first, timeRange[0]),
            std::min(t.second, timeRange[1])
        };

        if (newTimeRange[1] <= newTimeRange[0]) {
            // invalid range
            return false;
        }

        timeRange = newTimeRange;
    }
    return true;
}

//For a Ray with equation: 
//  point = origin + direction* time
//  time = (point - origin)/direction
float AABB::getTime(const int d, const glm::vec3 &origin, const glm::vec3 &direction, const glm::vec3 &v) const
{
    return (v[d] - origin[d]) / direction[d];
}