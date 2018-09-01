#include "ImageTexture.h"

#include "Image.h"

ImageTexture::ImageTexture(const Image * image)
    : image_(image)
{}

ImageTexture::~ImageTexture()
{}

glm::vec3 ImageTexture::color(const glm::vec2 & uv, const glm::vec3 & location) const
{
    return image_->getColor(uv);
}