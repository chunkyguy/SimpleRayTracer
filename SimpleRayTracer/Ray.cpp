//
//  Ray.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/7/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Ray.hpp"

glm::vec3 Ray::pointAt(float t) const {
	return _origin + (_direction * t);
}
