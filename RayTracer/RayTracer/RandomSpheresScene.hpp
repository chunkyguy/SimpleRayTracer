//
//  Scene.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/29/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "Scene.h"

class Camera;
class HitTestable;
class Material;
class Space;
class Texture;

class RandomSpheresScene : public Scene {
public:
    RandomSpheresScene(const glm::uvec2 &filmSize, const float resolution);

    virtual glm::vec3 getRandomLightOrigin() const;
    virtual float getLightArea() const;

};

#endif /* Scene_hpp */
