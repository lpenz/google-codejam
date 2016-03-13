/*
 * Compilation:
 * gcc -Wall -Werror -W -std=c++11 <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <stdint.h>
#include <algorithm>
#include <set>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

using namespace std;

void vec_show(ostream &o, vector<int> v) {
    for (auto i : v) o << i << " ";
}

static int64_t scalar_product(vector<int> v1, vector<int> v2) {
    int64_t rv = 0;

    for (unsigned int i = 0; i < v1.size(); i++)
        rv += int64_t(v1[i]) * int64_t(v2[i]);

    return rv;
}

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
        int n;
        fin >> n;
        vector<int> v1(n);
        vector<int> v2(n);
        for (int iv = 0; iv < n; iv++) fin >> v1[iv];
        for (int iv = 0; iv < n; iv++) fin >> v2[iv];

        /* solve case */
        set<int64_t> ps;
        sort(v1.begin(), v1.end());
        sort(v2.rbegin(), v2.rend());
        ps.insert(scalar_product(v1, v2));

        ostringstream answer("");
        answer << *ps.begin();

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}
