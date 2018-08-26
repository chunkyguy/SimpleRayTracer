#include "MovingSphere.h"

#include <algorithm>

#include "AABB.h"
#include "Intersection.hpp"
#include "Material.h"
#include "Ray.hpp"
#include "Sphere.hpp"

MovingSphere::MovingSphere(
    const glm::vec3 & center0, const glm::vec3 & center1, 
    const glm::vec2 & timeRange,
    float radius,
    const Material * material
) 
    : center0_(center0), center1_(center1), timeRange_(timeRange), radius_(radius), material_(material)
{}

std::unique_ptr<Intersection> MovingSphere::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    // get the sphere at current ray time
    Sphere s(getCenter(ray->getTime()), radius_, material_);
    return s.hit(ray, timeRange);
}

glm::vec3 MovingSphere::getCenter(const float time) const
{
    float factor = (time - timeRange_[0]) / (timeRange_[1] - timeRange_[0]);
    return center0_ + (center1_ - center0_) * factor;
}

std::unique_ptr<AABB> MovingSphere::boundingBox(const glm::vec2 & timeRange) const
{
    Sphere sLo(getCenter(timeRange[0]), radius_, material_);
    Sphere sHi(getCenter(timeRange[1]), radius_, material_);

    std::unique_ptr<AABB> boxLo = std::move(sLo.boundingBox(timeRange));
    std::unique_ptr<AABB> boxHi = std::move(sHi.boundingBox(timeRange));

    return std::make_unique<AABB>(boxLo.get(), boxHi.get());
}
