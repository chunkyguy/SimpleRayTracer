#include "NoiseTexture.h"

#include <glm\glm.hpp>

NoiseTexture::NoiseTexture(const float scale)
    : scale_(scale)
{}

NoiseTexture::~NoiseTexture()
{}

glm::vec3 NoiseTexture::color(const glm::vec2 & uv, const glm::vec3 & location) const
{
    return glm::vec3(1.0f) * noise_.generate(location * scale_);
}