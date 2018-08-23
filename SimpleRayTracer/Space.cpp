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

std::unique_ptr<Intersection> Space::hit(const Ray *ray, const std::array<float, 2> &range) const
{
    std::unique_ptr<Intersection> intersect;
    float lastDistance = range[1];
    for (std::vector<HitTestable *>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
        std::array<float, 2> lastRange = {range[0], lastDistance};
        std::unique_ptr<Intersection> localIntersects = (*it)->hit(ray, lastRange);
        if (localIntersects != nullptr) {
            lastDistance = localIntersects->getDistance();
            intersect = std::move(localIntersects);
        }
    }
    return intersect;
}
