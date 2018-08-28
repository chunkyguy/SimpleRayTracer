//
//  Space.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Space.hpp"

#include "AABB.h"
#include "Intersection.hpp"

Space::Space(const std::vector<const HitTestable *> &objects) :
_objects(objects)
{}

std::unique_ptr<Intersection> Space::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    std::unique_ptr<Intersection> intersect;
    float lastDistance = timeRange[1];
    for (std::vector<const HitTestable *>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
        std::unique_ptr<Intersection> localIntersects = (*it)->hit(ray, glm::vec2(timeRange[0], lastDistance));
        if (localIntersects != nullptr) {
            lastDistance = localIntersects->getDistance();
            intersect = std::move(localIntersects);
        }
    }
    return intersect;
}

std::unique_ptr<AABB> Space::boundingBox(const glm::vec2 & timeRange) const
{   
    std::unique_ptr<AABB> box, currBox;
    for (const HitTestable * object: _objects) {
        currBox = std::move(object->boundingBox(timeRange));

        if (!currBox) {
            // bounding box not possible - exit
            return currBox;
        }

        if (box) {
            box = std::move(std::make_unique<AABB>(currBox.get(), box.get()));
        } else {
            box = std::move(currBox);
        }
    }
    return box;
}
