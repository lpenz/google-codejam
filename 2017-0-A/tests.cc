#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

TEST(Sample, Case1)
{
  EXPECT_EQ("3", solve("---+-++-", 3));
}

TEST(Sample, Case2)
{
  EXPECT_EQ("0", solve("+++++", 4));
}

TEST(Sample, Case3)
{
  EXPECT_EQ("IMPOSSIBLE", solve("-+-+-", 4));
}
