#pragma once
#include <glm\glm.hpp>

class Texture
{
public:
    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const = 0;
};

