//
//  Space.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Space.hpp"
#include "Intersection.hpp"

Space::Space(const std::vector<HitTestable *> &objects) :
_objects(objects)
{}

bool Space::hit(const Ray &ray, const std::array<float, 2> &range, Intersection &intersect) const
{
    bool isIntersecting = false;
    float lastDistance = range[1];
    for (std::vector<HitTestable *>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
        std::array<float, 2> lastRange = {range[0], lastDistance};
        Intersection localIntersects;
        if ((*it)->hit(ray, lastRange, localIntersects)) {
            lastDistance = localIntersects.getDistance();
            intersect = localIntersects;
            isIntersecting = true;
        }
    }
    return isIntersecting;
}
