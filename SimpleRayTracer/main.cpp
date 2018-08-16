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

glm::vec3 getColor(
	const int targetWidth, const int targetHeight, const int resolution, 
	const int pointX, const int pointY,
	const Camera &camera, const Space &space)
{
	float r = float(pointX) / float(targetWidth);
	float g = float(pointY) / float(targetHeight);
	float b = 0.2f;

	return glm::vec3(r, g, b);

	//RandomNumGen rand;
	//glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	//for (int s = 0; s < resolution; ++s) {
	//	glm::vec2 uv = glm::vec2(float(pointX + rand.generate()) / float(targetWidth),
	//		float(pointY + rand.generate()) / float(targetHeight));
	//	Ray ray = camera.getRay(uv);
	//	color += Utils::trace(ray, space, 0);
	//}
	//glm::vec3 aggregateColor = color / float(resolution);
	//return glm::vec3(glm::sqrt(aggregateColor.x),
	//	glm::sqrt(aggregateColor.y),
	//	glm::sqrt(aggregateColor.z));
}

int main(int argc, const char * argv[]) 
{
	int targetWidth = 1200;
	int targetHeight = 800;
	int resolution = 10;

	glm::vec3 from = glm::vec3(13.0f, 2.0f, 3.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float fov = 20.0f;
	float aspectRatio = float(targetWidth) / float(targetHeight);
	float aperture = 0.1f;
	float focalDistance = 10.0f;
	Camera camera(from, target, up, fov, aspectRatio, aperture, focalDistance);

	Film film(glm::uvec2(targetWidth, targetHeight));

	Scene scene;
	const Space space = scene.getSpace();

	std::vector<glm::uvec2> points = film.getPoints();
	std::for_each(points.begin(), points.end(), [&](const glm::uvec2 &point) {
		glm::vec3 color = getColor(targetWidth, targetHeight, resolution, point.x, point.y, camera, space);
		film.updateColor(color, point);
	});

	film.process();

	return 0;
}
