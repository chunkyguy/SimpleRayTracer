#include "Material.h"
#include "Ray.hpp"

Material::Info::Info(const bool canScatter, const glm::vec3 & attenuation, const float pdf)
    : canScatter(canScatter), attenuation(attenuation), pdf(pdf)
{}
