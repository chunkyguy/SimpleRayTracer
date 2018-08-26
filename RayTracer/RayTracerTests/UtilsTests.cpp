#include "pch.h"

TEST(UtilsCase, ColorMapping)
{
    EXPECT_EQ(Utils::toColorSpace(glm::vec3(-1.0f, 0.0f, 1.0f)), glm::vec3(0.0f, 0.5f, 1.0f));
}

TEST(UtilsCase, NormalMapping)
{
    EXPECT_EQ(Utils::toNormalSpace(glm::vec3(0.0f, 0.5f, 1.0f)), glm::vec3(-1.0f, 0.0f, 1.0f));
}