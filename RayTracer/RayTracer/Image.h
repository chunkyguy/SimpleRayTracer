#pragma once
#include <string>

#include <glm\glm.hpp>

class Image
{
public:
    Image(const std::string &filename);
    ~Image();

    glm::vec3 getColor(const glm::vec2 &uv) const;

private:
    unsigned char *pixelData_;
    glm::uvec2 size_;
    int componentsPerPixel_;
};

