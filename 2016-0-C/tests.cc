#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

TEST(bv, Init)
{
    Solver s(3);
    int iend = 9;
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ(s.bv_[i], 1 + base * base);
    }
}

TEST(bv, N3)
{
    Solver s(3);
    int iend = 9;
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ(s.bv_[i], 1 + base * base);
        EXPECT_EQ("101", s.bv_[i].get_str(base));
    }
    s.incr();
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ("111", s.bv_[i].get_str(base));
    }
}

TEST(bv, N4)
{
    Solver s(4);
    int iend = 3;
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ("1001", s.bv_[i].get_str(base));
    }
    s.incr();
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ("1011", s.bv_[i].get_str(base));
    }
    s.incr();
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ("1101", s.bv_[i].get_str(base));
    }
    s.incr();
    for (int i = 0; i < iend; i++) {
        int base = i + 2;
        EXPECT_EQ("1111", s.bv_[i].get_str(base));
    }
}

TEST(primes, areprimes)
{
    auto it1 = Primes.end();
    auto it2 = it1;
    it1--;
    for (int i = 0; i < 50; i++) {
        it2 = it1;
        it1--;
        EXPECT_TRUE(PrimalityTester.isprime(*it1)) << "test of prime " << *it1;
        EXPECT_TRUE(PrimalityTester.isprime(*it2)) << "test of prime " << *it1;
    }
}

TEST(Sample, Case1)
{
    Solver s(6);
    s.fixJ();
    for (int i = 0; i < 9; i++) {
        int base = i + 2;
        EXPECT_EQ("100001", s.bv_[i].get_str(base));
    }
    cout << s.debug() << endl;
    for (int i = 0; i < 6; i++) {
        s.incrJ();
        cout << s.debug() << endl;
    }
}

#if 0
#endif
