#include "CoordinateSystem.h"

using namespace glm;

CoordinateSystem::CoordinateSystem(const glm::vec3 & normal)
{
    vec3 w = normalize(normal);
    vec3 a;
    if (fabs(w.x) > 0.9f) {
        a = vec3(0.0f, 1.0f, 0.0f);
    } else {
        a = vec3(1.0f, 0.0f, 0.0f);
    }
    vec3 v = normalize(cross(a, w));
    vec3 u = cross(v, w);

    u_ = u;
    v_ = v;
    w_ = w;
}

CoordinateSystem::~CoordinateSystem()
{}

glm::vec3 CoordinateSystem::convert(const glm::vec3 & v) const
{
    return v.x * u_ + v.y * v_ + v.z * w_;
}
