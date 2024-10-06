#include <gtest/gtest.h>

#include "Aabb.h"

TEST(AABB, InitIsEmpty)
{
    Aabb aabb;
    EXPECT_TRUE(aabb.empty());
}

TEST(AABB, SinglePointInit)
{
    Aabb aabb;
    const auto test = vec3f::random();
    EXPECT_FALSE(aabb.contains(test));

    aabb.growToInclude(test);
    EXPECT_TRUE(aabb.contains(test));
}

TEST(AABB, AlignedPoints)
{
    Aabb aabb;
    aabb.growToInclude({0.0f, 0.0f, 0.0f});
    aabb.growToInclude({1.0f, 0.0f, 0.0f});
    EXPECT_TRUE(aabb.contains({0.0f, 0.0f, 0.0f}));
    EXPECT_TRUE(aabb.contains({1.0f, 0.0f, 0.0f}));
    EXPECT_TRUE(aabb.contains({0.9f, 0.0f, 0.0f}));
    EXPECT_FALSE(aabb.contains({0.9f, 2.0f, 0.0f}));
    EXPECT_FALSE(aabb.contains({0.9f, 0.0f, 3.0f}));
}

TEST(AABB, RayIntersection)
{
    Aabb aabb;
    aabb.growToInclude({1.0f, 1.0f, 1.0f});
    aabb.growToInclude({2.0f, 2.0f, 2.0f});
    Ray rayHit({0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f});
    Ray rayFromInside({1.5f, 1.5f, 1.5f}, vec3f::random());
    Ray rayMiss({0.0f, 0.0f, 0.0f}, {2.0f, 0.5f, 1.5f});

    EXPECT_TRUE(aabb.intersect(rayHit));
    EXPECT_TRUE(aabb.intersect(rayFromInside));
    EXPECT_FALSE(aabb.intersect(rayMiss));
}
