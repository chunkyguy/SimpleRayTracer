//
//  Material.h
//  SimpleRayTracer
//
//  Created by Sidharth on 12/18/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Material_h
#define Material_h
#include <memory>
#include <glm\glm.hpp>

class Ray;
class Intersection;

class Material {
public:
    virtual std::unique_ptr<Ray> scatter (const Ray *ray, const Intersection *intersect, glm::vec3 &attenuation) const = 0;
};
#endif /* Material_h */
