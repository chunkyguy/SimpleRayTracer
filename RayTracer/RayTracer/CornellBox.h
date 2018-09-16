#pragma once
#include "Scene.h"

#include <glm\glm.hpp>

class CornellBox :
    public Scene
{
public:
    CornellBox(const glm::uvec2 &filmSize, const float resolution);
    
    virtual glm::vec3 getRandomLightOrigin() const;
    virtual float getLightArea() const;

private:
    const glm::vec2 lightRangeX_;
    const float lightY_;
    const glm::vec2 lightRangeZ_;
};
