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

int main(int argc, char *argv[]) {
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
        int N;
        fin >> N;
        map<int, int> wires;
        for (int i = 0; i < N; i++) {
            int a, b;
            fin >> a >> b;
            wires[a] = b;
        }

        /* solve case */
        int cross = 0;
        for (map<int, int>::iterator it1 = wires.begin(); it1 != wires.end();
             it1++) {
            int v1 = it1->second;
            for (map<int, int>::iterator it2 = it1; it2 != wires.end(); it2++) {
                if (v1 > it2->second) {
                    cross++;
                }
            }
        }
        ostringstream answer;
        answer << cross;

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}
