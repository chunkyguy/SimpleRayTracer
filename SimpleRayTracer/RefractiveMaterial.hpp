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
    virtual std::unique_ptr<Ray> scatter(const Ray *ray, const Intersection *intersect, glm::vec3 &attenuation) const;
    
private:
    float _refractiveIndex;
};

inline
RefractiveMaterial::RefractiveMaterial(const float refractiveIndex)
: _refractiveIndex(refractiveIndex)
{}

#endif /* RefractiveMaterial_hpp */
