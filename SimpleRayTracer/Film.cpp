//
//  Film.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/31/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Film.hpp"
#include <fstream>

Film::Film(const int x, const int y)
: _x(x), _y(y), _pixelData()
{}

void Film::updateColor(const glm::vec3 &color, const glm::uvec2 &point)
{
    _pixelData[getPosition(point)] = color;
}

int Film::getPosition(const glm::uvec2 &point) const
{
    return point.y * _x + point.x;
}

void Film::process() const
{
	std::ofstream file("image.ppm");

	file << "P3\n";
	file << _x << " " << _y << "\n";
	file << "255\n";

    for (int j = _y - 1; j >= 0; --j) {
        for (int i = 0; i < _x; ++i) {
            glm::vec3 color = _pixelData.at(getPosition(glm::uvec2(i, j)));
            glm::vec3 colorRGB = color * 255.0f;
            int rr = int(ceil(colorRGB.r));
            int gg = int(ceil(colorRGB.g));
            int bb = int(ceil(colorRGB.b));
            file << rr << " " << gg << " " << bb << "\n";
        }
    }
}
