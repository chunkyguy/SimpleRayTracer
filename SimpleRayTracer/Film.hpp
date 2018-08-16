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
#include <vector>
#include <glm\glm.hpp>

struct PixelData {
	glm::vec3 color;
	glm::uvec2 point;
};

// Store all color information. Not threadsafe
class Film {
public:
    Film(const glm::uvec2 &size);
	void updateData(const PixelData &data);
    void process() const;
	std::vector<glm::uvec2> getPoints() const;

private:
    
    int getPosition(const glm::uvec2 &point) const;
    
	glm::uvec2 size_;
    std::map<int, glm::vec3> _pixelData;
};

#endif /* Film_hpp */
