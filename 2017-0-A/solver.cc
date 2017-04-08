/*
 * Compilation:
 * gcc -Wall -Werror -W -std=c++11 <file>.cc -lgmpxx -lgmp
 *
 * This program uses the GNU multiple precision arithmetic library
 * (https://gmplib.org/)
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <bitset>
#include <string.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>
#include <gmpxx.h>

using namespace std;


string solve(const string& S0, uint32_t K) {
    string S(S0);
    reverse(S.begin(), S.end());

    // Create s number
    mpz_class s = 0;
    uint32_t i = 0;
    for (auto c: S) {
      if (c == '-') {
        s |= 1 << i;
      }
      i++;
    }
    uint32_t nbits = S.length() - K + 1;

    // Create unit
    mpz_class unit = 0;
    for (uint32_t i = 0; i < K; i++) {
      unit |= 1 << i;
    }

    // cout << "unit " << bitset<8>(unit.get_ui()) << " s " << bitset<8>(s.get_ui()) << " S " << S << " nbits " << nbits << endl;
    // Generate all numbers
    for (uint32_t i = 0; i <= (1u << nbits) - 1; i++) {
      mpz_class n = 0;
      uint32_t bits = 0;
      // Produce bit-by-bit:
      for (uint32_t j = 0; (1u << j) <= i; j++) {
        // cout << "unit " << hex << unit << " i " << i << " j " << j << " do " << ((1u << j) & i) << endl;;
        if ((1u << j) & i) {
          n ^= unit << j;
          bits ++;
        }
      }
      // cout << "unit " << hex << unit << " i " << i << " n " << hex << n << " s " << hex << s << endl;
      if (n == s) {
        ostringstream a;
        a << bits;
        return a.str();
      }
    }

    string a("IMPOSSIBLE");
    return a;
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
        string S;
        fin >> S;
        uint32_t K;
        fin >> K;

        /* solve case */
        ostringstream answer;
        answer << solve(S, K);

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
