//
//  ReflectiveMaterial.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/24/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef MetalMaterial_hpp
#define MetalMaterial_hpp

#include "Material.h"
#include "WLMath.hpp"

class ReflectiveMaterial : public Material {
public:
    ReflectiveMaterial(const glm::vec3 &albedo, const float fuzziness);

    virtual Info getScatterRay(const Ray *ray, const Intersection *intersect) const;
    virtual float getScatterPDF(const Ray *ray, const Ray *scatterRay, const Intersection *intersect) const;

private:
    glm::vec3 _albedo;
    float _fuzziness;
};

#endif /* MetalMaterial_hpp */
