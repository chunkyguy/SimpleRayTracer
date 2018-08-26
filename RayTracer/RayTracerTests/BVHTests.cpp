#include "pch.h"

struct StubHitTestable : public HitTestable
{
    glm::vec3 min_;
    glm::vec3 max_;

    virtual std::unique_ptr<Intersection> hit(const Ray *ray, const glm::vec2 &timeRange) const
    {
        return std::unique_ptr<Intersection>();
    }
    
    virtual std::unique_ptr<AABB> boundingBox(const glm::vec2 &timeRange) const
    {
        return std::make_unique<AABB>(min_, max_);
    }
};

TEST(BVHCase, EmptyList)
{
    glm::vec2 timeRange(0.0f);
    std::vector<HitTestable *> list = {};
    BVH bvh(list, timeRange);

    // TODO: test stuff
}
