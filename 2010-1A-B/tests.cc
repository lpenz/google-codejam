#include "gtest/gtest.h"
//#define DEBUG
#define NOMAIN
#include "solver.cc"

#if 0
#endif
TEST(base, empty)
{
    vector<int> l;
    EXPECT_EQ(0, solve(1, 1, 1, l));
}

TEST(base, elem1)
{
    vector<int> l{ 50 };
    EXPECT_EQ(0, solve(1, 1, 1, l));
}

TEST(elem2, ready)
{
    vector<int> l{ 50, 50 };
    EXPECT_EQ(0, solve(1, 1, 0, l));
}

TEST(elem2, del)
{
    vector<int> l{ 40, 50 };
    EXPECT_EQ(1, solve(1, 1, 1, l));
}

TEST(elem2, ins)
{
    vector<int> l{ 40, 50 };
    EXPECT_EQ(9, solve(999, 1, 1, l));
}

TEST(elem2, chg)
{
    vector<int> l{ 40, 50 };
    EXPECT_EQ(10, solve(999, 1, 0, l));
}

TEST(del, delbegin)
{
    vector<int> l{ 0, 50, 50 };
    EXPECT_EQ(1, solve(1, 99, 0, l));
}

TEST(del, delend)
{
    vector<int> l{ 50, 50, 0 };
    EXPECT_EQ(1, solve(1, 99, 0, l));
}

TEST(del, delmiddle)
{
    vector<int> l{ 50, 0, 50 };
    EXPECT_EQ(1, solve(1, 99, 0, l));
}

TEST(del, delmiddle3)
{
    vector<int> l{ 50, 50, 0, 0, 50, 50 };
    EXPECT_EQ(2, solve(1, 99, 0, l));
}

TEST(ins, ins1)
{
    vector<int> l{ 48, 50, 50 };
    EXPECT_EQ(1, solve(99, 1, 1, l));
}

TEST(ins, insN)
{
    vector<int> l{ 40, 50 };
    EXPECT_EQ(9, solve(99, 1, 1, l));
}

TEST(ins, insN2)
{
    vector<int> l{ 50, 40 };
    EXPECT_EQ(9, solve(99, 1, 1, l));
}

TEST(change, change0)
{
    vector<int> l{ 40, 50, 50 };
    EXPECT_EQ(9, solve(99, 99, 1, l));
}

TEST(change, change1)
{
    vector<int> l{ 50, 40, 50 };
    EXPECT_EQ(9, solve(99, 99, 1, l));
}

TEST(change, change2)
{
    vector<int> l{ 50, 50, 40 };
    EXPECT_EQ(9, solve(99, 99, 1, l));
}

TEST(inschange, inschange1)
{
    vector<int> l{ 40, 49 };
    EXPECT_EQ(2, solve(99, 1, 4, l));
}
#if 0
#endif
