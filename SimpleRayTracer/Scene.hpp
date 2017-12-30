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

class HitTestable;
class Space;

class Scene {
public:
    Scene();
    ~Scene();
    
    const Space getSpace() const;
    
private:
    
    std::vector<HitTestable *> _spheres;
};

#endif /* Scene_hpp */
