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
    ~SphereScene();

    virtual const Camera *getCamera() const;
    virtual std::unique_ptr<HitTestable> getScene() const;

private:
    std::vector<const Texture *> textures_;
    std::vector<const HitTestable *> shapes_;
    std::vector<const Material *> materials_;
    std::vector<const Image *> images_;
    const Camera *camera_;
};
