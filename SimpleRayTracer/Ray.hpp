//
//  Ray.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/7/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <glm\glm.hpp>

class Ray {
    glm::vec3 _origin;
    glm::vec3 _direction;
    
public:
    Ray();
    Ray(const glm::vec3 &origin, const glm::vec3 &dir);
    glm::vec3 getOrigin() const;
    glm::vec3 getDirection() const;
    glm::vec3 pointAt(float t) const;
};

inline
Ray::Ray()
: _origin(), _direction()
{}

inline
Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction)
: _origin(origin), _direction(direction)
{}

inline
glm::vec3 Ray::getOrigin() const
{
    return _origin;
}

inline
glm::vec3 Ray::getDirection() const
{
    return _direction;
}

#endif /* Ray_hpp */
