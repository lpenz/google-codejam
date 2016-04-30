#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

TEST(Sample, Case1)
{
    EXPECT_EQ("INSOMNIA", solve(0));
    EXPECT_EQ("10", solve(1));
    EXPECT_EQ("90", solve(2));
    EXPECT_EQ("110", solve(11));
    EXPECT_EQ("5076", solve(1692));
}

TEST(UpTo200, Case1)
{
    for (int i = 0; i < 200; i++) {
        cout << i << " -> " << solve(i) << endl;
    }
    EXPECT_TRUE(true);
}

TEST(UpTo1mil, Case1)
{
    for (int i = 200; i < 1000000; i++) {
        cout << i << " -> " << solve(i) << endl;
    }
    EXPECT_TRUE(true);
}
