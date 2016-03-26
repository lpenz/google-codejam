#include "gtest/gtest.h"

#define NOMAIN
#include "solver.cc"

Grid fromstring(int N, string s)
{
    Grid g;
    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            char cell = s[l * N + c + l];
            if (cell != '.')
                g[lc_t(l, c)] = cell;
        }
    }
    return g;
}

string tostring(int N, Grid g)
{
    ostringstream o;
    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            auto it = g.find(lc_t(l, c));
            if (it == g.end())
                o << '.';
            else
                o << it->second;
        }
        o << "\n";
    }
    return o.str();
}

class Winner : public ::testing::Test {
public:
    int N = 5;
    int K = 3;
    bool r = false;
    bool b = false;
};

#if 0

TEST(Grav, Grav)
{
    int N = 5;
    Grid g = fromstring(N, string(
                               "R....\n"
                               ".R...\n"
                               "..R..\n"
                               "...R.\n"
                               "....R\n"));
    Grid grav = gravity(N, g);
    EXPECT_EQ(tostring(N, grav), string(
                                     ".....\n"
                                     ".....\n"
                                     ".....\n"
                                     ".....\n"
                                     "RRRRR\n"));
}

TEST_F(Winner, Diag1)
{
    Grid g = fromstring(N, string(
                               "R....\n"
                               ".R...\n"
                               "..R..\n"
                               ".....\n"
                               ".....\n"));
    winner(N, K, g, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_FALSE(b);
}

TEST_F(Winner, Diag2)
{
    Grid g = fromstring(N, string(
                               ".R...\n"
                               "B.R..\n"
                               ".B.R.\n"
                               "..B..\n"
                               ".....\n"));
    winner(N, K, g, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_TRUE(b);
}

TEST_F(Winner, Diag3)
{
    Grid g = fromstring(N, string(
                               "..B..\n"
                               "...B.\n"
                               "R...B\n"
                               ".R...\n"
                               "..R..\n"));
    winner(N, K, g, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_TRUE(b);
}

TEST_F(Winner, Diag5)
{
    Grid g = fromstring(N, string(
                               ".....\n"
                               "..R..\n"
                               ".B.R.\n"
                               "..B.R\n"
                               "...B.\n"));
    winner(N, K, g, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_TRUE(b);
}

TEST_F(Winner, Diag6)
{
    Grid g = fromstring(N, string(
                               ".....\n"
                               ".....\n"
                               "..B..\n"
                               "...B.\n"
                               "....B\n"));
    winner(N, K, g, &r, &b);
    EXPECT_FALSE(r);
    EXPECT_TRUE(b);
}

TEST_F(Winner, Diag7)
{
    Grid g = fromstring(N, string(
                               "..R..\n"
                               ".R...\n"
                               "R...B\n"
                               "...B.\n"
                               "..B..\n"));
    winner(N, K, g, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_TRUE(b);
}

TEST_F(Winner, Diag8)
{
    Grid g = fromstring(N, string(
                               "....B\n"
                               "...B.\n"
                               "..B..\n"
                               ".R...\n"
                               "R....\n"));
    winner(N, 3, g, &r, &b);
    EXPECT_FALSE(r);
    EXPECT_TRUE(b);
}

TEST_F(Winner, Diag9)
{
    Grid g = fromstring(N, string(
                               ".....\n"
                               "..R.B\n"
                               ".R.B.\n"
                               "R.B..\n"
                               ".....\n"));
    winner(N, 3, g, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_TRUE(b);
}
#endif
TEST_F(Winner, case62)
{
    N = 29;
    Grid g = fromstring(N, string(
                               ".............................\n"
                               "..........B..................\n"
                               "..........R..................\n"
                               "..........B..................\n"
                               "..........R..................\n"
                               "..........B................R.\n"
                               "..........R................B.\n"
                               "....B.....B........R.......R.\n"
                               "....R....RB........RR......B.\n"
                               "....B....BR....R...BR....B.B.\n"
                               "....BB..RRB....B...RR....B.R.\n"
                               ".B..RB..RRRB..RBB.RRR.B..R.R.\n"
                               ".R.BRR.RBBBRB.BRR.RBB.B..B.BB\n"
                               ".B.RBB.BRRBBB.BRR.BRRRR..B.BR\n"
                               "BB.BRR.RBBRBBRRBB.RRRRR..R.BR\n"
                               "RB.RRR.BRBRRBRRBB.BRBBB.RR.RR\n"
                               "BB.RRR.BRRBRRBBRB.RBBBR.RR.BR\n"
                               "RRRRRB.RBRRBBRRBR.BRRBB.BBBRB\n"
                               "BRRBBBBBRRBRBBRBB.BRBBB.RBRRB\n"
                               "BRBRBBBRRRBBRRRBB.BBRRR.RRRRB\n"
                               "RRRRBBRBRBRRRBBRB.RRRBBBBRBRB\n"
                               "BBBBRRRBBBBRRBBBR.RBRBRBRRBRB\n"
                               "BRBRRBBRRRRRRBRBBBBBBBRBRBRBR\n"
                               "RRRBRBBRBBBRRBBRRRBBRBRBBRBRR\n"
                               "RBRRRBRRRRRBBBBRRBRRBRBRRRBRR\n"
                               "BBBBRRBRBBRBBRRRBRBBBBBBBRBBB\n"
                               "BBRBBRRBBRBRBRBRRBRBBBBBBRBBR\n"
                               "RBRBBBRRRBRRRBRBBRRRBRRRRBRBB\n"
                               "RRBRRBRBRRBRBBRRBBRRBBBBBRRRB\n"));
    Grid grot = rotate(N, g);
    Grid grav = gravity(N, grot);
    grid_print(N, grav);
    winner(N, 8, grav, &r, &b);
    EXPECT_TRUE(r);
    EXPECT_TRUE(b);
}
