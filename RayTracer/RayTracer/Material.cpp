#include "Material.h"
#include "Ray.hpp"

Material::Info::Info(const bool canScatter, const glm::vec3 & attenuation, const float pdf)
    : canScatter(canScatter), attenuation(attenuation), pdf(pdf)
{}

std::optional<glm::vec3> Material::getEmittedColor(const Ray * ray, const Intersection * intersect, const glm::vec2 & uv, const glm::vec3 & location) const
{
    return std::nullopt;
}