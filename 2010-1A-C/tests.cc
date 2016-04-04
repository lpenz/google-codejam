#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

#if 0
#endif
TEST(Win, Case1)
{
    Solver s;
    EXPECT_EQ(false, s.iswinning(4, 4, 0));
}

TEST(NotWin, Case1)
{
    Solver s;
    EXPECT_EQ(true, s.iswinning(8, 4, 0));
}

TEST(Solves, Case1)
{
    EXPECT_EQ(0, solve(0, 5, 5, 8, 8));
    EXPECT_EQ(0, solve(0, 8, 8, 5, 5));
}

TEST(Solves, Case2)
{
    EXPECT_EQ(1, solve(0, 11, 11, 2, 2));
    //EXPECT_EQ(1, solve(0, 2, 2, 11, 11));
}

TEST(Solves, Case3)
{
    EXPECT_EQ(20, solve(0, 1, 6, 1, 6));
}
