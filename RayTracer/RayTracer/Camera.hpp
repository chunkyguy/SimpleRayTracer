//
//  Camera.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/13/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp
#include <memory>
#include <glm/glm.hpp>
#include "RandomNumGen.hpp"

class Ray;

class Camera {
public:
    
    Camera(
        const glm::vec3 &from, const glm::vec3 &at, const glm::vec3 &up,
        const float fov, const float aspectRatio, const float aperture, const float focalDistance,
        const glm::vec2 &timeRange
    );

    std::unique_ptr<Ray> getRay(const glm::vec2 &uv) const;
    
private:
    
	glm::vec3 _origin;
	glm::vec3 _lowerLeft;
	glm::vec3 _horizontal;
	glm::vec3 _vertical;
    glm::mat3x3 _uvw;
    float _apperture;
    glm::vec2 timeRange_;
    RandomNumGen randGen_;
};

#endif /* Camera_hpp */
