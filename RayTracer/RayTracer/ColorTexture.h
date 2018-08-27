#pragma once
#include "Texture.h"

class ColorTexture : public Texture
{
public:
    ColorTexture(const glm::vec3 &color);
    ~ColorTexture();

    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const;

private:
    glm::vec3 color_;
};

