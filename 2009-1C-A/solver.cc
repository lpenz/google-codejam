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
#include <map>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

using namespace std;

uint64_t solve(string code)
{
    map<char, int> value;
    //map<int, char> ;

    value[code[0]] = 1;
    int num = 1;
    for (auto c : code) {
        auto d = value.find(c);
        if (d == value.end()) {
            if (num == 1)
                value[c] = 0;
            else
                value[c] = num;
            num++;
        }
    }

    int size = code.size();
    uint64_t ans = 0;
    int base = max(num, 2);
    for (int i = 0; i < size; i++) {
        int exp = (size - i - 1);
        uint64_t posval = 1;
        for (int j = 0; j < exp; j++) {
            posval *= base;
        }
        uint64_t incr = value[code[i]] * posval;
        //cout << "i " << i << "/" << size << " = " << code[i];
        //cout << " (" << value[code[i]] << ")";
        //cout << " base " << base;
        //cout << " ^ " << exp;
        //cout << " posval " << posval;
        //cout << " incr " << incr;
        //cout << endl;
        ans += incr;
    }
    //cout << "ans " << ans << endl;

    return ans;
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
        cout << "case " << icase << endl;
        /* read case */
        string code;
        fin >> code;

        uint64_t ans = solve(code);

        /* solve case */
        ostringstream answer("");
        answer << ans;

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
