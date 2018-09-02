//
//  Film.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/31/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Film.hpp"
#include <fstream>

Film::Film(const glm::uvec2 & size) 
	: size_(size) {
	pixelData_ = new glm::vec3[size.x * size.y];
}

Film::~Film() 
{
	delete[] pixelData_;
}

void Film::updateData(const PixelData & data) 
{
    pixelData_[getPosition(data.point)] = data.color;
}

std::vector<glm::uvec2> Film::getPoints() const {
	std::vector<glm::uvec2> points;
	for (unsigned int j = size_.y - 1; j >= 0; --j) {
		for (unsigned int i = 0; i < size_.x; ++i) {
			points.push_back(glm::uvec2(i, j));
		}
	}
	return points;
}

int Film::getPosition(const glm::uvec2 &point) const
{
	return point.x + (point.y * size_.x);
}

void Film::process() const
{
	std::ofstream file("image.ppm");

	file << "P3\n";
	file << size_.x << " " << size_.y << "\n";
	file << "255\n";

	std::vector<glm::uvec2> points = getPoints();
	for (std::vector<glm::uvec2>::const_iterator it = points.begin(); it != points.end(); ++it) {
		glm::vec3 color = pixelData_[getPosition(*it)];
		glm::vec3 colorRGB = color * 255.0f;
		int rr = int(ceil(colorRGB.r));
		int gg = int(ceil(colorRGB.g));
		int bb = int(ceil(colorRGB.b));
		file << rr << " " << gg << " " << bb << "\n";
	}
}
