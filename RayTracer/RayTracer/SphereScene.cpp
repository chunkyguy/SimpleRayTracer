#include "SphereScene.h"

#include "Camera.hpp"
#include "ColorTexture.h"
#include "DiffuseLightMaterial.h"
#include "Image.h"
#include "ImageTexture.h"
#include "LambertianMaterial.hpp"
#include "NoiseTexture.h"
#include "Plane.h"
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

    const HitTestable *sphere0 = new Sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, noiseMaterial);
    shapes_.push_back(sphere0);

    const Texture *colorTexture = new ColorTexture(vec3(4.0f));
    textures_.push_back(colorTexture);

    const Material *lightMaterial = new DiffuseLightMaterial(colorTexture);
    materials_.push_back(lightMaterial);

    const HitTestable *sphere1 = new Sphere(vec3(0.0f, 7.0f, 0.0f), 2.0f, lightMaterial);
    shapes_.push_back(sphere1);

    const HitTestable *lightPlane = new Plane(vec2(3, 1), vec2(5, 3), -2, lightMaterial);
    shapes_.push_back(lightPlane);

    camera_ = new Camera(
        vec3(0.0f, 3.0f, 20.0f), /* from */
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

const Camera * SphereScene::getCamera() const
{
    return camera_;
}

std::unique_ptr<HitTestable> SphereScene::getScene() const
{
    return std::unique_ptr<HitTestable>(new Space(shapes_));
}
