#include "ColorTexture.h"

ColorTexture::ColorTexture(const glm::vec3 & color)
    : color_(color)
{}

ColorTexture::~ColorTexture()
{}

glm::vec3 ColorTexture::color(const glm::vec2 & uv, const glm::vec3 & location) const
{
    return color_;
}