#pragma once
#include <vector>
#include "WLMath.hpp"

class Noise
{
public:
    Noise();
    ~Noise();

    float generate(const glm::vec3 &p) const;

private:
    std::vector<float> random_;
    std::vector<int> xIndices_;
    std::vector<int> yIndices_;
    std::vector<int> zIndices_;
};

