#include "Noise.h"

#include <algorithm>
#include <random>
#include "RandomNumGen.hpp"

Noise::Noise()
{
    RandomNumGen rand;

    for (int i = 0; i < 256; ++i) {
        random_.push_back(rand.generate());
        xIndices_.push_back(i);
        yIndices_.push_back(i);
        zIndices_.push_back(i);
    }

    std::vector<int> indices[3] = { xIndices_, yIndices_, zIndices_ };

    for (int i = 0; i < 3; ++i) {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(indices[i].begin(), indices[i].end(), g);
    }
}

Noise::~Noise()
{}

float Noise::generate(const glm::vec3 & p) const
{
    float u = p.x - floorf(p.x);
    float v = p.y - floorf(p.y);
    float w = p.z - floorf(p.z);

    int i = (static_cast<int>(p.x) * 4) & 255;
    int j = (static_cast<int>(p.y) * 4) & 255;
    int k = (static_cast<int>(p.z) * 4) & 255;

    return random_[xIndices_[i] ^ yIndices_[j] ^ zIndices_[k]];
}
