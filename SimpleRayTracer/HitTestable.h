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

class Intersection;
class Ray;

class HitTestable {
public:
    virtual bool hit(const Ray &ray, const std::array<float, 2> &range, Intersection &intersect) const = 0;
};

#endif /* HitTestable_h */
