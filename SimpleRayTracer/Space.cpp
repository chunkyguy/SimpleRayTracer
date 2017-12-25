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

Intersection Space::hit(const Ray &ray, const std::array<float, 2> &range) const
{
    Intersection intersects(false, 0, 0, 0);
    float distance = range[1];
    for (std::vector<HitTestable *>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
        std::array<float, 2> bestRange = {range[0], distance};
        Intersection localIntersects = (*it)->hit(ray, bestRange);
        if (localIntersects.isIntersecting) {
            distance = localIntersects.position;
            intersects = localIntersects;
        }
    }
    return intersects;
}
