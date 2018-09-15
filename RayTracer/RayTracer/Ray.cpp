//
//  Ray.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/7/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Ray.hpp"

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction, const float &time)
    : _origin(origin), _direction(glm::normalize(direction)), time_(time)
{}

glm::vec3 Ray::getOrigin() const
{
    return _origin;
}

glm::vec3 Ray::getDirection() const
{
    return _direction;
}

float Ray::getTime() const
{
    return time_;
}

glm::vec3 Ray::pointAt(float t) const {
	return _origin + (_direction * t);
}
