#include "Material.h"
#include "Ray.hpp"

Material::Info::Info(std::unique_ptr<Ray> ray, const glm::vec3 & attenuation)
    : ray(std::move(ray)), attenuation(attenuation)
{}
