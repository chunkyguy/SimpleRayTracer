#include "SphereScene.h"

#include "Camera.hpp"
#include "CheckerTexture.h"
#include "ColorTexture.h"
#include "LambertianMaterial.hpp"
#include "Sphere.hpp"
#include "Space.hpp"

using namespace glm;

SphereScene::SphereScene(const uvec2 & filmSize, const float resolution)
{
    const Texture *t1 = new ColorTexture(vec3(0.2f, 0.2f, 0.1f));
    const Texture *t2 = new ColorTexture(vec3(0.9f));
    const Texture *t = new CheckerTexture(t1, t2);
    textures_.push_back(t1);
    textures_.push_back(t2);
    textures_.push_back(t);

    const Material *m = new LambertianMaterial(t);
    materials_.push_back(m);

    const HitTestable *h1 = new Sphere(vec3(0.0f, -10.0f, 0.0f), 10.0f, m);
    const HitTestable *h2 = new Sphere(vec3(0.0f, 10.0f, 0.0f), 10.0f, m);
    shapes_.push_back(h1);
    shapes_.push_back(h2);

    camera_ = new Camera(
        vec3(13.0f, 2.0f, 13.0f), /* from */
        vec3(0.0f), /* at */
        vec3(0.0f, 1.0f, 0.0f), /* up */
        20.0f, /* fov */
        float(filmSize.x) / float(filmSize.y), /* aspect ratio */
        0.0f, /* aperture */
        10.0f, /* focal length */
        vec2(0.0f, 1.0f) /* time range */
    );
}

SphereScene::~SphereScene()
{
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

const Camera * SphereScene::getCamera() const
{
    return camera_;
}

std::unique_ptr<HitTestable> SphereScene::getScene() const
{
    return std::unique_ptr<HitTestable>(new Space(shapes_));
}
