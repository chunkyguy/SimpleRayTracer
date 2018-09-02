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

class Texture;

class LambertianMaterial : public Material {
public:
    LambertianMaterial(const Texture *albedo);

    virtual Material::Info getScatterRay(const Ray *ray, const Intersection *intersect) const;
    virtual std::optional<glm::vec3> getEmittedColor(const glm::vec2 &uv, const glm::vec3 &location) const;
    
private:

    const Texture *albedo_;
};

#endif /* LambertianMaterial_hpp */
