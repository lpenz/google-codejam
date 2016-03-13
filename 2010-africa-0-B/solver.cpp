/*
 * Compilation:
 * gcc <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <algorithm>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>

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
    string s;
    getline(fin, s);

    for (int icase = 1; icase <= N; icase++) {
        /* read case */
        getline(fin, s);

        /* solve case */
        istringstream iss(s);
        list<string> words;
        copy(istream_iterator<string>(iss), istream_iterator<string>(),
             front_inserter(words));

        ostringstream answer;
        for (list<string>::iterator it = words.begin(); it != words.end();
             ++it) {
            if (it != words.begin()) answer << " ";
            answer << *it;
        }

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}
