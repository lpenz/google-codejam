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
#include <set>
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
        cout << "Case #" << icase << endl;
        /* read case */
        int N, M;
        fin >> N >> M;
        set<string> dirs0;
        for (int i = 0; i < N; i++) {
            string d;
            fin >> d;
            dirs0.insert(d);
        }
        vector<string> pend(M);
        for (int i = 0; i < M; i++) fin >> pend[i];

        /* solve case */
        int mkdirs = 0;
        set<string> dirs(dirs0);
        for (auto d : pend) {
            std::stringstream ss(d);
            std::stringstream partial;
            std::string item;

            while (std::getline(ss, item, '/')) {
                if (item.empty()) continue;
                partial << "/" << item;
                if (dirs.find(partial.str()) == dirs.end()) {
                    mkdirs++;
                    dirs.insert(partial.str());
                }
            }
        }

        ostringstream answer;
        answer << mkdirs;

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}
