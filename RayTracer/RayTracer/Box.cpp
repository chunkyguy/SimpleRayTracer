#include "Box.h"

#include <vector>
#include <memory>
#include "WLMath.hpp"

#include "AABB.h"
#include "HitTestable.h"
#include "Intersection.hpp"
#include "Material.h"
#include "Plane.h"
#include "Space.hpp"

using namespace glm;

namespace
{
    vec2 xy(const vec3 &v)
    {
        return vec2(v.x, v.y);
    }
    vec2 yz(const vec3 &v)
    {
        return vec2(v.y, v.z);
    }
    vec2 xz(const vec3 &v)
    {
        return vec2(v.x, v.z);
    }
}

Box::Box(const vec3 &min, const vec3 &max, const Material *material)
    : min_(min), max_(max)
{
    std::vector<const HitTestable *> shapes;
    
    const HitTestable *left = new Plane(yz(min), yz(max), Edge::X, max.x, material, -1.0f);
    shapes.push_back(left);

    const HitTestable *right = new Plane(yz(min), yz(max), Edge::X, min.x, material, 1.0f);
    shapes.push_back(right);

    const HitTestable *top = new Plane(xz(min), xz(max), Edge::Y, max.y, material, 1.0f);
    shapes.push_back(top);

    const HitTestable *bottom = new Plane(xz(min), xz(max), Edge::Y, min.y, material, -1.0f);
    shapes.push_back(bottom);

    const HitTestable *far = new Plane(xy(min), xy(max), Edge::Z, max.z, material, 1.0f);
    shapes.push_back(far);

    const HitTestable *near = new Plane(xy(min), xy(max), Edge::Z, min.z, material, -1.0f);
    shapes.push_back(near);

    space_ = new Space(shapes);
}

Box::~Box()
{
    delete space_;
}

std::unique_ptr<Intersection> Box::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    return space_->hit(ray, timeRange);
}

std::unique_ptr<AABB> Box::boundingBox(const glm::vec2 & timeRange) const
{
    return std::make_unique<AABB>(min_, max_);
}

