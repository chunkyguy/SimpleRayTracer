#pragma once
#include "Texture.h"
#include "Noise.h"

class NoiseTexture :
    public Texture
{
public:
    NoiseTexture(const float scale);
    ~NoiseTexture();

    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const;

private:
    Noise noise_;
    const float scale_;
};
