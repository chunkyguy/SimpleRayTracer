//
//  Utils.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <glm\glm.hpp>

class Ray;
class HitTestable;

struct Utils {
    
    static
    glm::vec3 pointInUnitSphere();
    
    static
    glm::vec3 pointInUnitDisk();

    static
    glm::vec3 toColorSpace(glm::vec3 point);

    static
    glm::vec3 toNormalSpace(glm::vec3 p);

    static
    glm::vec3 trace(const Ray &ray, const HitTestable &item, const int &depth);
    
    static
    float fresnel(const float cosine, const float referactiveIndex);
};

#endif /* Utils_hpp */
