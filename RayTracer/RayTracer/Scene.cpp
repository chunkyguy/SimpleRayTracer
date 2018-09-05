#include "Scene.h"

#include "HitTestable.h"
#include "Image.h"
#include "Material.h"
#include "Space.hpp"
#include "Texture.h"

Scene::~Scene()
{
    for (const Image *i : images_) {
        delete i;
    }

    for (const Texture *t : textures_) {
        delete t;
    }

    for (const HitTestable *s : shapes_) {
        delete s;
    }

    for (const Material *m : materials_) {
        delete m;
    }
}

const Camera * Scene::getCamera() const
{
    return camera_;
}

std::unique_ptr<HitTestable> Scene::getScene() const
{
    return std::unique_ptr<HitTestable>(new Space(shapes_));
}
