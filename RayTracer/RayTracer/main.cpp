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
#include "CornellBox.h"

#define USE_CONCURRENT 1

struct RenderConfig
{
    // Render Quality LOW: Renders in few seconds
    static RenderConfig low()
    {
        return RenderConfig(5, glm::uvec2(240.0f, 160.0f), 10.0f);
    }

    // Render Quality MED: Renders within a minute
    static RenderConfig medium()
    {
        return RenderConfig(50, glm::uvec2(240.0f, 160.0f), 20.0f);
    }

    // Render Quality HIGH: Renders in a few minutes
    static RenderConfig high()
    {
        return RenderConfig(50, glm::uvec2(480.0f, 320.0f), 100.0f);
    }

    RenderConfig(int maxDepth, glm::uvec2 filmSize, float filmResolution)
        : maxDepth(maxDepth), filmSize(filmSize), filmResolution(filmResolution)
    {}

    int maxDepth;
    glm::uvec2 filmSize;
    float filmResolution;
};

struct SceneFactory
{
    enum class Name
    {
        randomSpheres,
        sphere,
        cornellBox
    };

    static std::unique_ptr<Scene> makeSceneNamed(const Name name, const RenderConfig &config)
    {
        switch (name) {
        case Name::sphere:
            return std::make_unique<SphereScene>(config.filmSize, config.filmResolution);
            break;
        case Name::randomSpheres:
            return std::make_unique<RandomSpheresScene>(config.filmSize, config.filmResolution);
            break;
        case Name::cornellBox:
            return std::make_unique<CornellBox>(config.filmSize, config.filmResolution);
            break;
        }
        
        return nullptr;
    }
};

int main(int argc, const char * argv[])
{
    RenderConfig config = RenderConfig::high();

    std::unique_ptr<Scene> scene = std::move(SceneFactory::makeSceneNamed(SceneFactory::Name::cornellBox, config));

    Film film(config.filmSize);

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
        data.color = Utils::getColor(
            glm::vec3(config.filmSize, config.filmResolution),
            point,
            scene->getCamera(),
            space.get(),
            config.maxDepth
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

// EOF
