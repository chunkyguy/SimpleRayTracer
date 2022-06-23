// main.cpp : Defines the entry point for the console application.
//

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
  #include "stdafx.h"
  #include <ppl.h>
  #include <concurrent_vector.h>
#endif

#include <cmath>

#include "WLMath.hpp"
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
  RenderConfig config = RenderConfig::medium();

  std::unique_ptr<Scene> scene = SceneFactory::makeSceneNamed(SceneFactory::Name::cornellBox, config);

  Film film(config.filmSize);

  // trace rays
  std::vector<glm::uvec2> points = film.getPoints();
  glm::uvec3 targetSize = glm::vec3(config.filmSize, config.filmResolution);

#if USE_CONCURRENT && _WIN32
  concurrency::concurrent_vector<PixelData> pixelData;

  concurrency::parallel_for_each(points.begin(), points.end(), [&](const glm::uvec2 &point) {
    PixelData data = {};
    data.point = point;
    data.color = Utils::getColor(targetSize, point, scene.get(), config.maxDepth);
    pixelData.push_back(data);
  });

  // generate image
  std::for_each(pixelData.begin(), pixelData.end(), [&](const PixelData &pixelData) {
      film.updateData(pixelData);
  });

  film.process();

#elif USE_CONCURRENT && __APPLE__
  dispatch_queue_t mainQueue = dispatch_get_main_queue();
  dispatch_queue_t rayQueue = dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0);
  dispatch_queue_t filmQueue = dispatch_queue_create("com.whackylabs.srt", DISPATCH_QUEUE_SERIAL);
  dispatch_group_t rayTask = dispatch_group_create();

  std::for_each(points.begin(), points.end(), [&](const glm::uvec2 &point) {
    dispatch_group_enter(rayTask);
    dispatch_async(rayQueue, ^{
      PixelData data = {};
      data.point = point;
      data.color = Utils::getColor(targetSize, point, scene.get(), config.maxDepth);
        dispatch_async(filmQueue, ^{
          film.updateData(data);
          dispatch_group_leave(rayTask);
        });
    });
  });

  dispatch_group_notify(rayTask, filmQueue, ^{
    film.process();
      dispatch_async(mainQueue, ^{
        exit(0);
      });
  });

  dispatch_main();

#else
  std::vector<PixelData> pixelData;

  std::for_each(points.begin(), points.end(), [&](const glm::uvec2 &point) {
    PixelData data = {};
    data.point = point;
    data.color = Utils::getColor(targetSize, point, scene.get(), config.maxDepth);
    pixelData.push_back(data);
  });

  // generate image
  std::for_each(pixelData.begin(), pixelData.end(), [&](const PixelData &pixelData) {
      film.updateData(pixelData);
  });

  film.process();

#endif

  return 0;
}

// EOF
