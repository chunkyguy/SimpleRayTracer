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
    Space(const std::vector<HitTestable *> &objects);
    virtual Intersection hit(const Ray &ray, const std::array<float, 2> &range) const;
    
private:
    std::vector<HitTestable *> _objects;
};

#endif /* Space_hpp */
