#include "DiffuseLightMaterial.h"

#include "Ray.hpp"
#include "Intersection.hpp"

DiffuseLightMaterial::DiffuseLightMaterial(const Texture * texture)
    : texture_(texture)
{}

DiffuseLightMaterial::~DiffuseLightMaterial()
{}

Material::Info DiffuseLightMaterial::getScatterRay(const Ray * ray, const Intersection * intersect) const
{
    return Material::Info(false, glm::vec3(0.0f), 1.0f);
}

std::optional<glm::vec3> DiffuseLightMaterial::getEmittedColor(const Ray * ray, const Intersection * intersect, const glm::vec2 & uv, const glm::vec3 & location) const
{
    if (glm::dot(intersect->getNormal(), ray->getDirection()) >= 0.0f) {
        return glm::vec3(0.0f);
    }
    return std::optional<glm::vec3>(texture_->color(uv, location));
}

float DiffuseLightMaterial::getScatterPDF(const Ray * ray, const Ray * scatterRay, const Intersection * intersect) const
{
    return 1.0f;
}
