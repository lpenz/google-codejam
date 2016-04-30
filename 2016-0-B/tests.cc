#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

TEST(Sample, Case1)
{
    EXPECT_EQ(1, solve("-"));
}

TEST(Sample, Case2)
{
    EXPECT_EQ(1, solve("-+"));
}

TEST(Sample, Case3)
{
    EXPECT_EQ(2, solve("+-"));
}

TEST(Sample, Case4)
{
    EXPECT_EQ(0, solve("+++"));
}

TEST(Sample, Case5)
{
    EXPECT_EQ(3, solve("--+-"));
}
