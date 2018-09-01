#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Texture.h"

class Image;

class ImageTexture :
    public Texture
{
public:
    ImageTexture(const Image *image);
    ~ImageTexture();

    virtual glm::vec3 color(const glm::vec2 &uv, const glm::vec3 &location) const;

private:
    const Image * image_;
};

