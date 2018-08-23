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
#include <glm\glm.hpp>

class ReflectiveMaterial : public Material {
public:
    ReflectiveMaterial(const glm::vec3 &albedo, const float fuzziness);
    virtual std::unique_ptr<Ray> scatter(const Ray *ray, const Intersection *intersect, glm::vec3 &attenuation) const;
    
private:
    glm::vec3 _albedo;
    float _fuzziness;
};

#endif /* MetalMaterial_hpp */
