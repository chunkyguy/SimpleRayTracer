//
//  Film.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/31/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Film.hpp"

#include <iostream>

Film::Film(const int x, const int y)
: _x(x), _y(y), _pixelData()
{}

void Film::updateColor(const glm::vec3 &color, const int i, const int j)
{
    _pixelData[getPosition(i, j)] = color;
}

int Film::getPosition(const int i, const int j) const
{
    return j * _x + i;
}

void Film::process() const
{
    std::cout << "P3" << std::endl;
    std::cout << _x << " " << _y << std::endl;
    std::cout << "255" << std::endl;

    for (int j = _y - 1; j >= 0; --j) {
        for (int i = 0; i < _x; ++i) {
            glm::vec3 color = _pixelData.at(getPosition(i, j));
            glm::vec3 colorRGB = color * 255.0f;
            int rr = int(ceil(colorRGB.r));
            int gg = int(ceil(colorRGB.g));
            int bb = int(ceil(colorRGB.b));
            std::cout << rr << " " << gg << " " << bb << std::endl;
        }
    }
}
