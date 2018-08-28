#pragma once
#include <memory>

class Camera;
class HitTestable;

class Scene
{
public:
    virtual const Camera *getCamera() const = 0;
    virtual std::unique_ptr<HitTestable> getScene() const = 0;
};
