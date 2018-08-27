#pragma once
#include "Texture.h"

class CheckerTexture : public Texture
{
public:
    CheckerTexture(const Texture *first, const Texture *second);
    ~CheckerTexture();

    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const;

private:
    const Texture *first_;
    const Texture *second_;
};

