//
//  LambertianMaterial.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/20/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef LambertianMaterial_hpp
#define LambertianMaterial_hpp
#include <glm\glm.hpp>
#include "Material.h"

class LambertianMaterial : public Material {
public:
    LambertianMaterial(const glm::vec3 &albedo);
    
    virtual
    bool scatter(const Ray &ray, const Intersection &intersect, glm::vec3 &attenuation, Ray &bounce) const;
    
private:
    glm::vec3 _albedo;
};

inline
LambertianMaterial::LambertianMaterial(const glm::vec3 &albedo)
: _albedo(albedo)
{}

#endif /* LambertianMaterial_hpp */
