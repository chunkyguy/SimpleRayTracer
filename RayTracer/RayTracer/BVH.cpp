#include "BVH.h"

#include "AABB.h"
#include "Intersection.hpp"
#include "RandomNumGen.hpp"
#include "WLAssert.h"

BVH::BVH(std::vector<HitTestable *> list, const glm::vec2 & timeRange)
    : left_(nullptr), right_(nullptr), timeRange_(timeRange), hasChildren_(false)
{
    // sort array
    RandomNumGen rGen;
    int axis = static_cast<int>(rGen.generate() * 3.0f);
    std::sort(list.begin(), list.end(), [axis](HitTestable *l, HitTestable *r) {
        glm::vec2 zeroRange(0.0f);
        std::unique_ptr<AABB> lBox = std::move(l->boundingBox(zeroRange));
        std::unique_ptr<AABB> rBox = std::move(r->boundingBox(zeroRange));

        wlAssert(lBox.get() != nullptr, "No left bounding box available");
        wlAssert(rBox.get() != nullptr, "No right bounding box available");

        glm::vec3 lMin = lBox->getMin();
        glm::vec3 rMin = rBox->getMin();

        wlAssert(axis >= 0 && axis <= 2, "Out of range");
        return lMin[axis] < rMin[axis];
    });

    // assign left/right child
    switch (list.size()) {
    case 0:
        left_ = right_ = nullptr;
        hasChildren_ = false;
        break;

    case 1:
        left_ = right_ = list[0];
        hasChildren_ = false;
        break;

    case 2:
        left_ = list[0];
        right_ = list[1];
        hasChildren_ = false;
        break;

    default:
        left_ = new BVH(std::vector<HitTestable *>(list.begin(), list.begin() + list.size() / 2), timeRange);
        right_ = new BVH(std::vector<HitTestable *>(list.begin() + list.size() / 2, list.end()), timeRange);
        hasChildren_ = true;
        break;
    }
}

BVH::~BVH()
{
    if (hasChildren_) {
        delete left_;
        delete right_;
    }
}

std::unique_ptr<Intersection> BVH::hit(const Ray * ray, const glm::vec2 & timeRange) const
{
    if (! boundingBox()->hit(ray, timeRange)) {
        return std::unique_ptr<Intersection>();
    }

    std::unique_ptr<Intersection> lIntersect = std::move(left_->hit(ray, timeRange));
    std::unique_ptr<Intersection> rIntersect = std::move(right_->hit(ray, timeRange));

    if (lIntersect && rIntersect) {
        if (lIntersect->getDistance() < rIntersect->getDistance()) {
            return lIntersect;
        } else {
            return rIntersect;
        }
    } else if (lIntersect) {
        return lIntersect;
    } else if (rIntersect) {
        return rIntersect;
    } else {
        return std::unique_ptr<Intersection>();
    }
}

std::unique_ptr<AABB> BVH::boundingBox() const
{
    std::unique_ptr<AABB> lBox = std::move(left_->boundingBox(timeRange_));
    std::unique_ptr<AABB> rBox = std::move(right_->boundingBox(timeRange_));

    wlAssert(lBox.get() != nullptr, "No left bounding box available");
    wlAssert(rBox.get() != nullptr, "No right bounding box available");

    if (lBox && rBox) {
        return std::make_unique<AABB>(lBox.get(), rBox.get());
    } else {
        return std::unique_ptr<AABB>();
    }
}

std::unique_ptr<AABB> BVH::boundingBox(const glm::vec2 & timeRange) const
{
    return boundingBox();
}
