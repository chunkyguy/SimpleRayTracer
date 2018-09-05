#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Scene.h"

class Camera;
class Material;
class Texture;
class Image;

class SphereScene :
    public Scene
{
public:
    SphereScene(const glm::uvec2 &filmSize, const float resolution);

private:
};
