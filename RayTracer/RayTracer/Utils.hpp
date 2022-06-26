//
//  Utils.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/10/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp
#include <memory>
#include "WLMath.hpp"

class Camera;
class Ray;
class Scene;

struct Utils
{
    static glm::vec3 getColor(
        const glm::uvec3 &targetSize,
        const glm::uvec2 point,
        const Scene *scene,
        const int maxDepth
    );

    static glm::vec3 pointInUnitSphere();

    static glm::vec3 pointInUnitDisk();

    static glm::vec3 randomCosineDirection();

    // [-1, +1] -> [0, 1]
    static glm::vec3 toColorSpace(glm::vec3 point);

    // [0, 1] -> [-1, +1]
    static glm::vec3 toNormalSpace(glm::vec3 p);

    static float fresnel(const float cosine, const float referactiveIndex);
};

#endif /* Utils_hpp */
