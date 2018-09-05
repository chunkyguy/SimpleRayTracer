#pragma once
#include <memory>
#include <vector>

class Camera;
class HitTestable;
class Image;
class Material;
class Texture;

class Scene
{
public:
    virtual ~Scene();

    const Camera *getCamera() const;
    std::unique_ptr<HitTestable> getScene() const;

protected:
    std::vector<const Texture *> textures_;
    std::vector<const HitTestable *> shapes_;
    std::vector<const Material *> materials_;
    std::vector<const Image *> images_;
    const Camera *camera_;
};
