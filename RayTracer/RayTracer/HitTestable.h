//
//  HitTestable.h
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef HitTestable_h
#define HitTestable_h
#include <array>
#include <memory>
#include <glm\glm.hpp>

class Intersection;
class Ray;
class AABB;

class HitTestable {
public:
    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const = 0;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const = 0;
};

#endif /* HitTestable_h */
