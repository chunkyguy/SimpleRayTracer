#include "SphereScene.h"

#include "Camera.hpp"
#include "NoiseTexture.h"
#include "LambertianMaterial.hpp"
#include "Sphere.hpp"
#include "Space.hpp"

using namespace glm;

SphereScene::SphereScene(const uvec2 & filmSize, const float resolution)
{
    const Texture *noiseTexture = new NoiseTexture(4.0f);
    textures_.push_back(noiseTexture);

    const Material *noiseMaterial = new LambertianMaterial(noiseTexture);
    materials_.push_back(noiseMaterial);

    const HitTestable *background = new Sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, noiseMaterial);
    shapes_.push_back(background);

    const HitTestable *sphere = new Sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, noiseMaterial);
    shapes_.push_back(sphere);

    camera_ = new Camera(
        vec3(13.0f, 2.0f, 3.0f), /* from */
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
