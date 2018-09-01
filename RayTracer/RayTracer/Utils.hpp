//
//  Utils.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp
#include <memory>
#include <glm\glm.hpp>

class Ray;
class HitTestable;

struct Utils {
    
    static
    glm::vec3 pointInUnitSphere();
    
    static
    glm::vec3 pointInUnitDisk();

    // [-1, +1] -> [0, 1]
    static
    glm::vec3 toColorSpace(glm::vec3 point);

    // [0, 1] -> [-1, +1]
    static
    glm::vec3 toNormalSpace(glm::vec3 p);

    static
    glm::vec3 trace(const std::unique_ptr<Ray> ray, const HitTestable *item, const int depth, const int maxDepth);
    
    static
    float fresnel(const float cosine, const float referactiveIndex);
};

#endif /* Utils_hpp */
