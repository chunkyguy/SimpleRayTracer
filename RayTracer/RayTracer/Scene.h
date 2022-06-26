#pragma once
#include <memory>
#include <vector>

#include "WLMath.hpp"

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
    const HitTestable* getSpace() const;

    virtual glm::vec3 getRandomLightOrigin() const = 0;
    virtual float getLightArea() const = 0;

protected:
    void init();
    
    std::vector<const Texture *> textures_;
    std::vector<const HitTestable *> shapes_;
    std::vector<const Material *> materials_;
    std::vector<const Image *> images_;
    const Camera *camera_;

private:
    std::unique_ptr<HitTestable> space_;
};
