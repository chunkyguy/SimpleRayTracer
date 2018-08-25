#include "MovingSphere.h"
#include "Material.h"
#include "Ray.hpp"
#include "Intersection.hpp"

MovingSphere::MovingSphere(
    const glm::vec3 & center0, const glm::vec3 & center1, 
    const glm::vec2 & timeRange,
    float radius,
    const Material * material
) 
    : center0_(center0), center1_(center1), timeRange_(timeRange), radius_(radius), material_(material)
{}

std::unique_ptr<Intersection> MovingSphere::hit(const Ray *ray, const std::array<float, 2>& range) const
{
    glm::vec3 center = ray->getOrigin() - getCenter(ray->getTime());
    glm::vec3 direction = ray->getDirection();

    float a = glm::dot(direction, direction);
    float b = 2.0f * glm::dot(center, direction);
    float c = glm::dot(center, center) - (radius_ * radius_);
    float d = (b * b) - (4.0f * a * c);

    if (d > 0) {
        float root0 = (-b - glm::sqrt(d)) / (a * 2.0f);
        float root1 = (-b + glm::sqrt(d)) / (a * 2.0f);
        if (root0 > range[0] && root0 < range[1]) {
            glm::vec3 point = ray->pointAt(root0);
            return std::make_unique<Intersection>(root0, point, (point - getCenter(ray->getTime())) / radius_, material_);
        } else if (root1 > range[0] && root1 < range[1]) {
            glm::vec3 point = ray->pointAt(root1);
            return std::make_unique<Intersection>(root1, point, (point - getCenter(ray->getTime())) / radius_, material_);
        }
    }

    return std::unique_ptr<Intersection>();
}

glm::vec3 MovingSphere::getCenter(const float time) const
{
    float factor = (time - timeRange_[0]) / (timeRange_[1] - timeRange_[0]);
    return center0_ + (center1_ - center0_) * factor;
}
