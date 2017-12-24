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

struct HitTestable {
    virtual ~HitTestable();
    virtual bool hit(const Ray &ray, const std::array<float, 2> &range, Intersection &intersect) const = 0;
};

inline
HitTestable::~HitTestable()
{}

#endif /* HitTestable_h */
