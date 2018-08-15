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

glm::vec3 getColor(const int nx, const int ny, const int ns,
	const int i, const int j,
	const Camera &camera, const Space &space) {
	RandomNumGen rand;
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int s = 0; s < ns; ++s) {
		glm::vec2 uv = glm::vec2(float(i + rand.generate()) / float(nx),
			float(j + rand.generate()) / float(ny));
		Ray ray = camera.getRay(uv);
		color += Utils::trace(ray, space, 0);
	}
	glm::vec3 aggregateColor = color / float(ns);
	return glm::vec3(glm::sqrt(aggregateColor.x),
		glm::sqrt(aggregateColor.y),
		glm::sqrt(aggregateColor.z));
}

int main(int argc, const char * argv[]) {

	int nx = 1200;
	int ny = 800;
	int ns = 10;

	glm::vec3 from = glm::vec3(13.0f, 2.0f, 3.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float fov = 20.0f;
	float aspectRatio = float(nx) / float(ny);
	float aperture = 0.1f;
	float focalDistance = 10.0f;
	Camera camera(from, target, up, fov, aspectRatio, aperture, focalDistance);

	Film film(nx, ny);

	Scene scene;
	const Space space = scene.getSpace();

	concurrency::concurrent_vector<glm::uvec2> points;
	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			points.push_back(glm::uvec2(i, j));
		}
	}

	concurrency::parallel_for_each(points.begin(), points.end(), [&](const glm::uvec2 & point) {
		glm::vec3 color = getColor(nx, ny, ns, point.x, point.y, camera, space);
		film.updateColor(color, point);
	});

	film.process();

	return 0;
}
