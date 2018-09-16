#include "Scene.h"

#include "HitTestable.h"
#include "Image.h"
#include "Material.h"
#include "Space.hpp"
#include "Texture.h"
#include "WLAssert.h"

void Scene::init()
{
    space_.reset(new Space(shapes_));
}

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

const HitTestable* Scene::getSpace() const
{
    wlAssert(space_.get() != nullptr, "Did not call init()");
    return space_.get();
}
