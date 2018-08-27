#include "CheckerTexture.h"
#include <cmath>

CheckerTexture::CheckerTexture(const Texture * first, const Texture * second)
    : first_(first), second_(second)
{}

CheckerTexture::~CheckerTexture()
{}

glm::vec3 CheckerTexture::color(const glm::vec2 & uv, const glm::vec3 & location) const
{
    float s = std::sinf(10.0f * location.x) * sinf(10.0f * location.y) * sinf(10.0f * location.z);
    if (s < 0.0f) {
        return first_->color(uv, location);
    } else {
        return second_->color(uv, location);
    }
}
