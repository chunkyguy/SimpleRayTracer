#pragma once
#include "Texture.h"
#include "Noise.h"

class NoiseTexture :
    public Texture
{
public:
    NoiseTexture();
    ~NoiseTexture();

    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const;

private:
    Noise noise_;
};
