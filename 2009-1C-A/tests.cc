#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

TEST(TestVal, Case1)
{
    auto ans = solve("10123456789");
    EXPECT_EQ(ans, 10123456789);
}

TEST(TestMaxVal, Case1)
{
    auto ans = solve("100000000023456789");
    EXPECT_EQ(ans, 100000000023456789);
}

TEST(TestMaxLen, Case1)
{
    auto ans = solve("1000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(ans, pow(2, 60));
}

TEST(TestSingle, Case1)
{
    auto ans = solve("111111111");
    EXPECT_EQ(ans, pow(2, 9) - 1);
}
