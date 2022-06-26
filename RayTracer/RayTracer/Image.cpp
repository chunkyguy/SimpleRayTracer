#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Image::Image(const std::string & filename)
    : pixelData_(nullptr), size_(), componentsPerPixel_(0)
{
    int x, y;
   pixelData_= stbi_load(filename.c_str(), &x, &y, &componentsPerPixel_, 0);
   size_ = glm::uvec2(x, y);
}

Image::~Image()
{
    stbi_image_free(pixelData_);
}

glm::vec3 Image::getColor(const glm::vec2 & uv) const
{
    int s = static_cast<int>(glm::clamp(uv.x * size_.x, 0.0f, size_.x - 1.0f));
    int t = static_cast<int>(glm::clamp((1.0f - uv.y) * size_.y - 0.001f, 0.0f, size_.y - 1.0f));

    return glm::vec3(
        pixelData_[3 * s + 3 * size_.x * t] / 255.0f,
        pixelData_[3 * s + 3 * size_.x * t + 1] / 255.0f,
        pixelData_[3 * s + 3 * size_.x * t + 2] / 255.0f
    );
}
