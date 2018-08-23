//
//  main.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/6/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include <cmath>

#include <ppl.h>
#include <concurrent_vector.h>
#include <glm\glm.hpp>

#include "Camera.hpp"
#include "Film.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Space.hpp"
#include "Utils.hpp"

#define USE_CONCURRENT 1

glm::vec3 getColor(
    const glm::uvec3 &targetSize,
	const glm::uvec2 point,
    const Camera *camera,
    const Space *space)
{
	RandomNumGen rand;
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	for (unsigned int s = 0; s < targetSize.z; ++s) {
		glm::vec2 uv = glm::vec2(
			float(point.x + rand.generate()) / float(targetSize.x),
			float(point.y + rand.generate()) / float(targetSize.y)
		);
		color += Utils::trace(std::move(camera->getRay(uv)), space, 0);
	}
	glm::vec3 aggregateColor = color / float(targetSize.z);
	return glm::vec3(glm::sqrt(aggregateColor.x),
		glm::sqrt(aggregateColor.y),
		glm::sqrt(aggregateColor.z));
}

int main(int argc, const char * argv[]) 
{
	Scene scene;
	Film film(scene.getFilmSize());

	// trace rays
	std::vector<glm::uvec2> points = film.getPoints();

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
            glm::vec3(scene.getFilmSize(), scene.getFilmResolution()),
           point,
            scene.getCamera(),
            scene.getSpace()
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
