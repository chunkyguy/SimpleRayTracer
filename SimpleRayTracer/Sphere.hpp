//
//  Sphere.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp
#include <glm\glm.hpp>
#include "HitTestable.h"

class Material;

class Sphere: public HitTestable {
public:
    Sphere(const glm::vec3 &center, float radius, const Material *material);
    virtual ~Sphere();
    
    virtual
    bool hit(const Ray &ray, const std::array<float, 2> &range, Intersection &intersect) const;

private:
    glm::vec3 _center;
    float _radius;
    const Material *_material;
};

#endif /* Sphere_hpp */
