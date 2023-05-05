#include <gtest/gtest.h>

TEST(Hello, BasicAssersions) {
    EXPECT_STRNE("Hello", "gtest");
    EXPECT_EQ(7*6, 42);
}