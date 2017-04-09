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

static inline uint8_t digit(const char c) {
  return c - '0';
}

static inline bool istidy(const string &s) {
  for (size_t i = 1; i < s.length(); i++) {
    if (digit(s[i]) < digit(s[i-1])) {
      return false;
    }
  }
  return true;
}

string solve(const string& N_) {
  string s(N_);
  while (! istidy(s)) {
    cout << s << " " << istidy(s) << endl;
    int i = s.length() - 1;
    for (; i >= 0 && ! istidy(s); i--) {
      cout << "0 i " << i << " s[i] " << s[i] << " s " << s << " istidy " << istidy(s) << endl;
      if (s[i] == '9') {
        continue;
      }
      s[i] = '9';
      cout << "1 i " << i << " s[i] " << s[i] << " s " << s << endl;
      for (int j = i - 1; j >= 0; j--) {
        if (s[j] != '0') {
          s[j]--;
          break;
        }
        s[j] = '9';
      }
      cout << "2 i " << i << " s[i] " << s[i] << " s " << s << endl;
    }
    while (s[0] == '0') {
      s.erase(0, 1);
    }
  }
  cout << "s " << s << endl;
  return s;
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
    string N;
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
