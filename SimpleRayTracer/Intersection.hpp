//
//  Intersection.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Intersection_hpp
#define Intersection_hpp

struct Intersection {
    
    Intersection(bool isIntersecting, float point);
    
    bool isIntersecting;
    float point;
};

inline
Intersection::Intersection(bool isIntersecting, float point)
: isIntersecting(isIntersecting), point(point)
{}

#endif /* Intersection_hpp */
