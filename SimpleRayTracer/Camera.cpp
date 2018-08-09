//
//  Camera.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

Camera::Camera(const glm::vec3 &from, const glm::vec3 &at, const glm::vec3 &up,
	const float fov, const float aspectRatio, const float aperture, const float focalDistance) {

	float angle = fov * M_PI / 180.0f;
	float halfHeight = glm::tan(angle / 2.0f);
	float halfWidth = halfHeight * aspectRatio;

	// camera basis vectors
	glm::vec3 w = glm::normalize(from - at);
	glm::vec3 u = glm::normalize(glm::cross(up, w));
	glm::vec3 v = glm::cross(w, u);

	_lowerLeft = from - (halfWidth * focalDistance * u) - (halfHeight * focalDistance * v) - (focalDistance * w);
	_horizontal = 2.0f * halfWidth * focalDistance * u;
	_vertical = 2.0f * halfHeight * focalDistance * v;
	_origin = from;
	_apperture = aperture;
	_uvw = glm::mat3x3(u, v, w);
}

Ray Camera::getRay(const glm::vec2 &uv) const {
	glm::vec3 point = (_apperture / 2.0f) * Utils::pointInUnitDisk();
	glm::vec3 offset = (_uvw[0] * point.x) + (_uvw[1] * point.y);
	glm::vec3 origin = _origin + offset;
	glm::vec3 direction = _lowerLeft + (_horizontal * uv.x) + (_vertical * uv.y) - _origin - offset;
	return Ray(origin, direction);
}