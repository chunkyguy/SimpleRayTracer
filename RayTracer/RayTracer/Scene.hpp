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

class Camera;
class HitTestable;
class Material;
class Space;

class Scene {
public:
    Scene();
    ~Scene();

    const glm::uvec2 getFilmSize() const;
    const float getFilmResolution() const;
	const Camera *getCamera() const;
    const Space *getSpace() const;
    
private:
    glm::uvec2 filmSize_;
    float filmResolution_;
	Camera *camera_;
    Space *space_;
    std::vector<HitTestable *> spheres_;
    std::vector<Material *> materials_;
};

#endif /* Scene_hpp */
