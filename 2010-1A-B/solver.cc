/*
 * Compilation:
 * gcc -Wall -Werror -W -std=c++11 <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <assert.h>
#include <stdio.h>

#define DEBUG

using namespace std;

struct Solver {
    int dp[256][256];
    int D;
    int I;
    int M;

    Solver(int D, int I, int M)
        : D(D)
        , I(I)
        , M(M)
    {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                if (i == 0)
                    dp[i][j] = 0;
                else
                    dp[i][j] = INT32_MAX;
            }
        }
    }

    int solve(vector<int>& v)
    {
        int cbest = INT32_MAX;

        for (int vnext = 0; vnext < 256; vnext++)
            cbest = min(cbest, solve2(v, v.size(), vnext));

        return cbest;
    }

    void solve2pars(vector<int>& v, int len, int vnext)
    {
        return;

        auto it = begin(v);
        advance(it, len);
        copy(begin(v), it, ostream_iterator<int>(std::cout, " "));
        cout << " len " << len << " for vnext " << vnext;
    }

    int solve2(vector<int>& v, int len, int vnext)
    {
        if (dp[len][vnext] != INT32_MAX)
            return dp[len][vnext];

        solve2pars(v, len, vnext);
        //cout << endl;

        /* del */
        int cbest = solve2(v, len - 1, vnext) + D;
        ostringstream b("del");

        /* change + ins */
        int vpos = v[len - 1];
        if (M == 0) {
            /* no ins allowed */
            int cprev = solve2(v, len - 1, vnext);
            int cchg = abs(vpos - vnext);
            int c = cprev + cchg;
            if (c < cbest) {
                b.str("");
                b << "with"
                  << " cchg " << cchg
                  << " c " << c;
                cbest = c;
            }
        } else {
            /* change vpos -> vnew, for all possible vnew */
            /* ins what is left for vnext */
            for (int vnew = 0; vnew < 256; vnew++) {
                int cprev = solve2(v, len - 1, vnew);
                int nins;
                if (vnew != vnext)
                    nins = (abs(vnew - vnext) - 1) / M;
                else
                    nins = 0;
                int cins = nins * I;
                int cchg = abs(vpos - vnew);
                int c = cprev + cins + cchg;
                //cout << "vnew " << vnew << " nins " << nins << " cins " << cins << " cchg " << cchg << " c " << c << endl;
                if (c < cbest) {
                    b.str("");
                    b << "with"
                      << " vpos " << vpos
                      << " vnew " << vnew
                      << " cprev " << cprev
                      << " nins " << nins
                      << " cins " << cins
                      << " cchg " << cchg
                      << " c " << c;
                    cbest = c;
                }
            }
        }

        dp[len][vnext] = cbest;
        solve2pars(v, len, vnext);
        //cout << " cbest " << cbest << " " << b.str() << endl;

        return cbest;
    }
};

int solve(const int D __attribute__((unused)),
          const int I __attribute__((unused)),
          const int M,
          vector<int>& a)
{
    cout << "D " << D << " I " << I << " M " << M << endl;
    Solver s(D, I, M);
    int cbest = s.solve(a);
    return cbest;
}

int do_main(int argc, char* argv[])
{
    assert(argc == 3);

    /* open and read file passed as first command-line argument */
    ifstream fin(argv[1], fstream::in);

    /* open output file */
    ostringstream sout;
    sout << argv[2] << ".tmp";
    ofstream fout(sout.str().c_str(), fstream::out);

    /* read number of cases */
    int T;
    fin >> T;

    for (int icase = 1; icase <= T; icase++) {
        /* read case */
        int D, I, M, N;
        cout << "case " << icase << endl;
        fin >> D >> I >> M >> N;
        vector<int> a;
        for (int i = 0; i < N; i++) {
            int input;
            fin >> input;
            a.push_back(input);
        }

        /* solve case */
        ostringstream answer;
        int cbest = solve(D, I, M, a);
        answer << cbest;

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}

#ifndef NOMAIN
int main(int argc, char* argv[])
{
    return do_main(argc, argv);
}
#endif
