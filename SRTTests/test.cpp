#include "pch.h"
#include "glm\glm.hpp"
#include "../SimpleRayTracer/AABB.h"
#include "../SimpleRayTracer/Ray.hpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(AABB, Hit)
{
    glm::vec3 min(1.0f, 1.0f, 1.0f);
    glm::vec3 max(2.0f, 2.0f, 2.0f);
    AABB box(min, max);

    Ray ray(glm::vec3(0.0f), glm::vec3(1.0f), 0.0f);
    EXPECT_TRUE(box.hit(ray, glm::vec2(0.0f, 1.0f)));
}