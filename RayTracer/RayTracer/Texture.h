#pragma once
#include "WLMath.hpp"

class Texture
{
public:
    virtual ~Texture() {};
    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const = 0;
};

