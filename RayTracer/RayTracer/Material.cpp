#include "Material.h"
#include "Ray.hpp"

Material::Info::Info(std::unique_ptr<Ray> ray, const glm::vec3 & attenuation, const float pdf)
    : ray(std::move(ray)), attenuation(attenuation), pdf(pdf)
{}
