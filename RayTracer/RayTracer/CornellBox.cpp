#include "CornellBox.h"

#include "Box.h"
#include "Camera.hpp"
#include "ColorTexture.h"
#include "DiffuseLightMaterial.h"
#include "HitTestable.h"
#include "LambertianMaterial.hpp"
#include "Plane.h"
#include "RandomNumGen.hpp"

using namespace glm;

CornellBox::CornellBox(const uvec2 & filmSize, const float resolution)
    : lightRangeX_({ 213.0f, 343.0f }), lightY_(554.0f), lightRangeZ_({227.0f, 332.0f})
{
    const Texture * redTexture = new ColorTexture(vec3(0.65, 0.05, 0.05));
    const Material *redMat = new LambertianMaterial(redTexture);
    textures_.push_back(redTexture);
    materials_.push_back(redMat);

    const Texture * whiteTexture = new ColorTexture(vec3(0.73, 0.73, 0.73));
    const Material *whiteMat = new LambertianMaterial(whiteTexture);
    textures_.push_back(whiteTexture);
    materials_.push_back(whiteMat);

    const Texture * greenTexture = new ColorTexture(vec3(0.12, 0.45, 0.15));
    const Material *greenMat = new LambertianMaterial(greenTexture);
    textures_.push_back(greenTexture);
    materials_.push_back(greenMat);

    const Texture *lightTexure = new ColorTexture(vec3(15, 15, 15));
    const Material *lightMat = new DiffuseLightMaterial(lightTexure);
    textures_.push_back(lightTexure);
    materials_.push_back(lightMat);

    const HitTestable *left = new Plane(vec2(0,0), vec2(555,555), Edge::X, 0, redMat, 1.0f);
    shapes_.push_back(left);

    const HitTestable *right = new Plane(vec2(0, 0), vec2(555, 555), Edge::X, 555, greenMat, -1.0f);
    shapes_.push_back(right);
    
    const HitTestable *light = new Plane(
        vec2(lightRangeX_[0], lightRangeZ_[0]), 
        vec2(lightRangeX_[1], lightRangeZ_[1]), 
        Edge::Y, lightY_, lightMat, -1.0f
    );
    shapes_.push_back(light);
    
    const HitTestable *top = new Plane(vec2(0, 0), vec2(555, 555), Edge::Y, 555, whiteMat, -1.0f);
    shapes_.push_back(top);

    const HitTestable *bottom = new Plane(vec2(0,0), vec2(555, 555), Edge::Y, 0, whiteMat, 1.0f);
    shapes_.push_back(bottom);
    
    const HitTestable *far = new Plane(vec2(0, 0), vec2(555, 555), Edge::Z, 555, whiteMat, -1.0f);
    shapes_.push_back(far);

    const HitTestable *box0 = new Box(vec3(130, 0, 65), vec3(295, 165, 230), whiteMat);
    shapes_.push_back(box0);

    const HitTestable *box1 = new Box(vec3(265, 0, 295), vec3(430, 330, 460), whiteMat);
    shapes_.push_back(box1);

    camera_ = new Camera(
        vec3(278, 278, -800), /* from */
        vec3(278, 278, 0), /* at */
        vec3(0.0f, 1.0f, 0.0f), /* up */
        40.0f, /* fov */
        float(filmSize.x) / float(filmSize.y), /* aspect ratio */
        0.0f, /* aperture */
        10.0f, /* focal length */
        vec2(0.0f, 1.0f) /* time range */
    );

    init();
}

glm::vec3 CornellBox::getRandomLightOrigin() const
{
    RandomNumGen rGen;
    return glm::vec3 {
        rGen.generate(lightRangeX_),
        lightY_,
        rGen.generate(lightRangeZ_)
    };
}

float CornellBox::getLightArea() const
{
    return (lightRangeX_[1] - lightRangeX_[0]) * (lightRangeZ_[1] - lightRangeZ_[0]);
}
