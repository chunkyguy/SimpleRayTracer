//
//  Material.h
//  SimpleRayTracer
//
//  Created by Sidharth on 12/18/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Material_h
#define Material_h
#include <optional>
#include <memory>
#include <glm\glm.hpp>

class Ray;
class Intersection;

class Material {
public:

    struct Info
    {
        Info(const bool canScatter, const glm::vec3 &attenuation, const float pdf);

        bool canScatter;
        glm::vec3 attenuation;
        float pdf;
    };

    virtual Info getScatterRay(const Ray *ray, const Intersection *intersect) const = 0;
    virtual std::optional<glm::vec3> getEmittedColor(const glm::vec2 &uv, const glm::vec3 &location) const = 0;
    virtual float getScatterPDF(const Ray *ray, const Ray *scatterRay, const Intersection *intersect) const = 0;
};
#endif /* Material_h */
