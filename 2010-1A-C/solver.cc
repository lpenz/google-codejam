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
#include <map>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

using namespace std;

#if 0
struct Solver {
    map<pair<int, int>, bool> result;

    bool iswinning(int big, int small, int depth)
    {
        pair<int, int> k(big, small);
        auto it = result.find(k);
        if (it != result.end())
            return it->second;

        string depthstr = string(depth * 4, ' ');
        //cout << depthstr << big << "," << small << " depth " << depth << endl;
        if (big == small) {
            //cout << depthstr
            //     << " arya got " << big << "," << small
            //     << " and lost"
            //     << endl;
            return false;
        }
        /* always starts at arya move */
        for (int ka = big / small; ka > 0; --ka) {
            int big2 = max(small, big - ka * small);
            int small2 = min(small, big - ka * small);

            /* if this is a winning move, arya plays it */
            if (big2 == small2) {
                //cout << depthstr
                //     << " ka " << ka
                //     << " arya left " << big2 << "," << small2
                //     << " and won"
                //     << endl;
                result[k] = true;
                return true;
            }
            if (small2 <= 0) {
                //cout << depthstr
                //     << " ka " << ka
                //     << " arya left " << big2 << "," << small2
                //     << " and lost"
                //     << endl;
                continue;
            }

            /* bryan */
            bool aryawins = true;
            for (int kb = big2 / small2; kb > 0; --kb) {
                int big3 = max(small2, big2 - kb * small2);
                int small3 = min(small2, big2 - kb * small2);

                //cout << depthstr
                //     << " ka " << ka
                //     << " kb " << kb
                //     << " arya left " << big2 << "," << small2
                //     << " bryan left " << big3 << "," << small3;
                if (small3 <= 0) {
                    //cout
                    //    << " and bryan lost"
                    //    << endl;
                    continue;
                }
                if (big3 == small3) {
                    //cout
                    //    << " and bryan won"
                    //    << endl;
                    aryawins = false;
                    break;
                }

                //cout << endl;

                if (!iswinning(big3, small3, depth + 1)) {
                    //cout << depthstr
                    //     << " ka " << ka
                    //     << " kb " << kb
                    //     << " bryan escaped"
                    //     << endl;
                    aryawins = false;
                    break;
                }
            }
            if (aryawins) {
                //cout << depthstr
                //     << " ka " << ka
                //     << " arya left " << big2 << "," << small2
                //     << " arya wins for all kb!"
                //     << endl;
                result[k] = true;
                return true;
            }
        }
        //cout << depthstr
        //     << " bryan escaped somehow"
        //     << endl;
        result[k] = false;
        return false;
    }
};
#endif

struct Solver {
    bool iswinning(int big, int small, int depth)
    {
        if (small == 0)
            return true;
        if (big >= 2 * small)
            return true;
        bool r = !iswinning(small, big - small, depth + 1);
        return r;
    }
};

int
solve(int icase, int A1, int A2, int B1, int B2)
{
    Solver s;
    cout << icase << " " << A1 << " " << A2 << " " << B1 << " " << B2 << endl;
    int r = 0;
    for (int a = A1; a <= A2; a++) {
        if (B2 >= 2 * a) {
            r += B2 - 2 * a;
        }
        if (B1 >= 2 * a) {
            r -= B1 - 2 * a - 1;
            continue;
        }
        if (a >= 2 * B2) {
            r += B2 - B1 + 1;
            continue;
        }
        for (int b = B1; b <= min(2 * a, B2); b++) {
            bool w = s.iswinning(max(a, b), min(a, b), 0);
            if (w)
                r++;
        }
    }
    return r;
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
        int A1, A2, B1, B2;
        fin >> A1 >> A2 >> B1 >> B2;

        /* solve case */
        ostringstream answer;
        answer << solve(icase, A1, A2, B1, B2);

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
