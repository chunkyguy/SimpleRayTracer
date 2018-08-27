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

    virtual std::unique_ptr<Ray> scatter(const Ray *ray, const Intersection *intersect, glm::vec3 &attenuation) const;
    
private:

    const Texture *albedo_;
};

inline
LambertianMaterial::LambertianMaterial(const Texture *albedo)
: albedo_(albedo)
{}

#endif /* LambertianMaterial_hpp */
