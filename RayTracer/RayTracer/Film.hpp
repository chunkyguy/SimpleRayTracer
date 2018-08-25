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
	~Film();
	void updateData(const PixelData &data);
    void process() const;
	std::vector<glm::uvec2> getPoints() const;

private:
    
    int getPosition(const glm::uvec2 &point) const;
    
	glm::uvec2 size_;
	glm::vec3 *pixelData_;
 };

#endif /* Film_hpp */
