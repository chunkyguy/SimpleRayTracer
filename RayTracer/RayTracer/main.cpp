// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cmath>

#include <ppl.h>
#include <concurrent_vector.h>
#include <glm\glm.hpp>

#include "Camera.hpp"
#include "Film.hpp"
#include "HitTestable.h"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "RandomSpheresScene.hpp"
#include "SphereScene.h"
#include "Utils.hpp"

#define USE_CONCURRENT 1
#define MODE_RELEASE 0

glm::vec3 getColor(
    const glm::uvec3 &targetSize,
    const glm::uvec2 point,
    const Camera *camera,
    const HitTestable *space,
    const int maxDepth
);


int main(int argc, const char * argv[])
{
#if MODE_RELEASE
    int maxDepth = 50;
    glm::uvec2 filmSize(480.0f, 320.0f);
    float filmResolution = 100.0f;
#else 
    int maxDepth = 5;
    glm::uvec2 filmSize(120.0f, 80.0f);
    float filmResolution = 10.0f;
#endif
    Scene *scene;
    // scene = new RandomSpheresScene(
    scene = new SphereScene(
        filmSize,
        filmResolution
    );

    Film film(filmSize);

    // trace rays
    std::vector<glm::uvec2> points = film.getPoints();

    std::unique_ptr<HitTestable> space = std::move(scene->getScene());

#if USE_CONCURRENT
    concurrency::concurrent_vector<PixelData> pixelData;
    concurrency::parallel_for_each(
#else
    std::vector<PixelData> pixelData;
    std::for_each(
#endif
        points.begin(), points.end(), [&](const glm::uvec2 &point) {
        PixelData data = {};
        data.point = point;
        data.color = getColor(
            glm::vec3(filmSize, filmResolution),
            point,
            scene->getCamera(),
            space.get(),
            maxDepth
        );
        pixelData.push_back(data);
    });

    // generate image
    std::for_each(pixelData.begin(), pixelData.end(), [&](const PixelData &pixelData) {
        film.updateData(pixelData);
    });
    film.process();

    return 0;
}

glm::vec3 getColor(
    const glm::uvec3 &targetSize,
    const glm::uvec2 point,
    const Camera *camera,
    const HitTestable *space,
    const int maxDepth)
{
    RandomNumGen rand;
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
    for (unsigned int s = 0; s < targetSize.z; ++s) {
        glm::vec2 uv = glm::vec2(
            float(point.x + rand.generate()) / float(targetSize.x),
            float(point.y + rand.generate()) / float(targetSize.y)
        );
        color += Utils::trace(std::move(camera->getRay(uv)), space, 0, maxDepth);
    }
    glm::vec3 aggregateColor = color / float(targetSize.z);
    return glm::vec3(glm::sqrt(aggregateColor.x),
        glm::sqrt(aggregateColor.y),
        glm::sqrt(aggregateColor.z)
    );
}

// EOF
