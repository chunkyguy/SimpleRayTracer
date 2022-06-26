#pragma once
#include "WLMath.hpp"
#include "Edge.h"

class CoordinateSystem
{
public:
    CoordinateSystem(const glm::vec3 &normal);
    ~CoordinateSystem();

    glm::vec3 convert(const glm::vec3 &v) const;
    glm::vec3 getU() const;
    glm::vec3 getV() const;
    glm::vec3 getW() const;

private:
    glm::vec3 u_, v_, w_;
};

inline
glm::vec3 CoordinateSystem::getU() const
{
    return u_;
}

inline
glm::vec3 CoordinateSystem::getV() const
{
    return v_;
}

inline
glm::vec3 CoordinateSystem::getW() const
{
    return w_;
}
