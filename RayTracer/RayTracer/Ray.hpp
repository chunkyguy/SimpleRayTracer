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
public:
    Ray(const glm::vec3 &origin, const glm::vec3 &dir, const float &time);
    glm::vec3 getOrigin() const;
    glm::vec3 getDirection() const;
    glm::vec3 pointAt(float t) const;
    float getTime() const;
    
private:
    glm::vec3 _origin;
    glm::vec3 _direction;
    float time_;
};
#endif /* Ray_hpp */
