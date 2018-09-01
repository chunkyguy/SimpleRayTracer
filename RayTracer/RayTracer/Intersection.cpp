//
//  Intersection.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Intersection.hpp"

Intersection::Intersection(
    const float time,
    const glm::vec3 & point,
    const glm::vec3 & normal,
    const glm::vec2 & uv,
    const Material * material
) : time_(time), point_(point), normal_(normal), uv_(uv), material_(material)
{}

float Intersection::getTime() const
{
    return time_;
}
glm::vec3 Intersection::getPoint() const
{
    return point_;
}

glm::vec3 Intersection::getNormal() const
{
    return normal_;
}

const Material *Intersection::getMaterial() const
{
    return material_;
}

glm::vec3 Intersection::getTarget() const
{
    return point_ + normal_;
}

glm::vec2 Intersection::getUV() const
{
    return uv_;
}
