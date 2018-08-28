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
    ~RandomSpheresScene();

    virtual const Camera *getCamera() const;
    virtual std::unique_ptr<HitTestable> getScene() const;

private:
	Camera *camera_;
    std::vector<const HitTestable *> spheres_;
    std::vector<Material *> materials_;
    std::vector<const Texture *> textures_;
};

inline const Camera *RandomSpheresScene::getCamera() const
{
    return camera_;
}

#endif /* Scene_hpp */
