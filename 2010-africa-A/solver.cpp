/*
 * Compilation:
 * gcc <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <stdint.h>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {
    assert(argc == 3);

    /* open and read file passed as first command-line argument */
    ifstream fin(argv[1], fstream::in);

    /* open output file */
    ostringstream sout;
    sout << argv[2] << ".tmp";
    ofstream fout(sout.str().c_str(), fstream::out);

    /* read number of cases */
    int N;
    fin >> N;

    for (int icase = 1; icase <= N; icase++) {
        /* read case */
        int C, I;
        fin >> C;
        fin >> I;
        map<int, set<int>> ps;
        for (int i = 1; i <= I; i++) {
            int price;
            fin >> price;
            ps[price].insert(i);
        };

        /* solve case */
        ostringstream answer;
        for (map<int, set<int>>::iterator it = ps.begin(); it != ps.end();
             ++it) {
            if (C - it->first == it->first) {
                /* equal values */
                if (it->second.size() < 2) continue;
                set<int>::iterator i = it->second.begin();
                answer << *i;
                i++;
                answer << " " << *i;
                break;
            }
            map<int, set<int>>::iterator itother = ps.find(C - it->first);
            if (itother == ps.end()) continue;
            vector<int> ans({*it->second.begin(), *itother->second.begin()});
            sort(ans.begin(), ans.end());
            for (vector<int>::iterator i = ans.begin(); i != ans.end(); ++i) {
                if (i != ans.begin()) answer << " ";
                answer << *i;
            }
            break;
        }

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}
