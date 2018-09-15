//
//  RefractiveMaterial.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/25/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef RefractiveMaterial_hpp
#define RefractiveMaterial_hpp

#include "Material.h"

class RefractiveMaterial : public Material {
public:
    
    RefractiveMaterial(const float refractiveIndex);

    virtual Info getScatterRay(const Ray *ray, const Intersection *intersect) const;
    virtual std::optional<glm::vec3> getEmittedColor(const glm::vec2 &uv, const glm::vec3 &location) const;
    virtual float getScatterPDF(const Ray *ray, const Ray *scatterRay, const Intersection *intersect) const;

private:
    float _refractiveIndex;
};

#endif /* RefractiveMaterial_hpp */
