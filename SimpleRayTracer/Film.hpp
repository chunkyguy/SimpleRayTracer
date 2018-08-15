//
//  Film.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/31/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Film_hpp
#define Film_hpp
#include <map>
#include <glm\glm.hpp>

// Store all color information. Not threadsafe
class Film {
public:
    Film(const int x, const int y);
    void updateColor(const glm::vec3 &color, const glm::uvec2 &point);
    void process() const;
    
private:
    
    int getPosition(const glm::uvec2 &point) const;
    
    int _x;
    int _y;
    std::map<int, glm::vec3> _pixelData;
};

#endif /* Film_hpp */
