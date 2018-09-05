#pragma once
#include "Scene.h"

#include <glm\glm.hpp>

class CornellBox :
    public Scene
{
public:
    CornellBox(const glm::uvec2 &filmSize, const float resolution);
};

