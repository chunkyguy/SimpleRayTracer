//
//  Space.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Space_hpp
#define Space_hpp
#include <vector>
#include "HitTestable.h"

class Space: public HitTestable {
public:
    Space(const std::vector<const HitTestable *> &objects);

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const;
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const;

private:
    std::vector<const HitTestable *> _objects;
};

#endif /* Space_hpp */
