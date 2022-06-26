//
//  Intersection.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Intersection_hpp
#define Intersection_hpp
#include "WLMath.hpp"

class Material;
class Ray;

class Intersection {
public:
    Intersection(const float time, const glm::vec3 &point, const glm::vec3 &normal, const glm::vec2 &uv, const Material *material);

    glm::vec3 getTarget() const;
    glm::vec3 getPoint() const;
    glm::vec2 getUV() const;
    float getTime() const;
    glm::vec3 getNormal() const;
    const Material *getMaterial() const;

private:
    float time_;
    glm::vec2 uv_;
    glm::vec3 point_;
    glm::vec3 normal_;
    const Material *material_;
};

#endif /* Intersection_hpp */
