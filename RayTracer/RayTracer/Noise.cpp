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

    // hermite cubic smoothing
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);

    int i = static_cast<int>(floorf(p.x));
    int j = static_cast<int>(floorf(p.y));
    int k = static_cast<int>(floorf(p.z));

    float value = 0.0f;

    for (int a = 0; a < 2; ++a) {
        for (int b = 0; b < 2; ++b) {
            for (int c = 0; c < 2; ++c) {
               float f = random_[xIndices_[(i + a) & 255] ^ yIndices_[(j + b) & 255] ^ zIndices_[(k + c) & 255]];
               // trilinear interpolation
               value += (a * u + (1 - a) * (1 - u)) * (b * v + (1 - b) * (1 - v)) * (c * w + (1 - c) * (1 - w)) * f;
            }
        }
    }

    return value;
}
