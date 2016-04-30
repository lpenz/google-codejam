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
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

using namespace std;

/*
       EFGHINORSTUVWXZ | S |
ZERO   1     11      1 | Z |
TWO          1  1  1   | W |
FOUR    1    11  1     | U |
SIX        1   1    1  | X |
EIGHT  1 111    1      | G |

THREE  1  1   1 1      | H |
FIVE   11  1      1    | F |
SEVEN  1    1  1  1    | V |

NINE   1   11          | E |
ONE    1    11         | N |
*/

string solve(string S)
{
    /* calculate the number of each char: */
    map<char, int> numchars;

    for (auto s : S) {
        auto it = numchars.find(s);
        if (it == numchars.end()) {
            numchars[s] = 1;
        } else {
            numchars[s] = it->second + 1;
        }
    }

    /* fill in the number of each digit */
    vector<int> nums(9);
    nums[0] = numchars['Z'];
    nums[2] = numchars['W'];
    nums[4] = numchars['U'];
    nums[6] = numchars['X'];
    nums[8] = numchars['G'];
    nums[3] = numchars['H'] - nums[8];
    nums[5] = numchars['F'] - nums[4];
    nums[7] = numchars['S'] - nums[6];
    nums[9] = numchars['I'] - nums[6] - nums[8] - nums[5];
    nums[1] = numchars['N'] - 2 * nums[9] - nums[7];

    ostringstream ans("");
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j < nums[i]; j++) {
            ans << i;
        }
    }

    return ans.str();
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

        /* solve case */
        string answer(solve(S));

        /* store solution */
        fout << "Case #" << icase << ": " << answer << endl;
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
