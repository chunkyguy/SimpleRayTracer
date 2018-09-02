#pragma once
#include <glm\glm.hpp>
#include "Material.h"
#include "Texture.h"

class DiffuseLightMaterial : public Material
{
public:
    DiffuseLightMaterial(const Texture *texture);
    ~DiffuseLightMaterial();

    virtual Info getScatterRay(const Ray *ray, const Intersection *intersect) const;
    virtual std::optional<glm::vec3> getEmittedColor(const glm::vec2 &uv, const glm::vec3 &location) const;

private:
    const Texture * texture_;
};
