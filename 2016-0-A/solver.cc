/*
 * Compilation:
 * gcc -Wall -Werror -W -std=c++11 <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <string.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

using namespace std;

string solve(int N)
{
    if (N == 0)
        return "INSOMNIA";

    uint8_t digits[10];
    uint8_t done[10];

    memset(done, 1, 10);

    uint64_t iN = N;
    while (memcmp(digits, done, 10) != 0) {
        uint64_t tmp = iN;
        while (tmp > 0) {
            digits[tmp % 10] = 1;
            tmp /= 10;
        }
        iN += N;
    }
    ostringstream a;
    a << (iN - N);
    return a.str();
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
        uint64_t N;
        fin >> N;

        /* solve case */
        ostringstream answer;
        answer << solve(N);

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
