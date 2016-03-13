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

int analyse(const set<string> &accel, const set<string> &dict,
            const string left, const string right) {
    int rv = 0;

    if (right.size() == 0) {
        // cout << "find " << left << endl;
        if (dict.find(left) != dict.end()) return 1;
        return 0;
    }

    int leftsize = left.size();
    if (leftsize > 0) {
        if (accel.find(left) == accel.end()) {
            return 0;
        }
    }

    string::const_iterator l = right.begin();
    string leftnew(left);
    while (*l != '(' && l != right.end()) {
        leftnew += *l;
        l++;
    }
    if (*l == '(') {
        l++;
        string::const_iterator e(l);
        while (*e != ')') e++;
        e++;
        while (*l != ')') {
            string leftnew2(leftnew);
            leftnew2 += *l;
            string rightnew(e, right.end());
            rv += analyse(accel, dict, leftnew2, rightnew);
            l++;
        }
    } else {
        string rightnew(l, right.end());
        rv += analyse(accel, dict, leftnew, rightnew);
    }
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

    /* read initial data */
    int L;
    fin >> L;
    int D;
    fin >> D;
    int N;
    fin >> N;

    /* read dictionary */
    set<string> dict;
    set<string> accel;
    for (int d = 1; d <= D; d++) {
        string word;
        fin >> word;
        dict.insert(word);
        string w;
        for (string::iterator iw = word.begin() + 1; iw != word.end(); ++iw) {
            if (iw != word.begin()) {
                string n(word.begin(), iw);
                accel.insert(n);
            }
        }
    }

    for (int icase = 1; icase <= N; icase++) {
        /* read case */
        string pat;
        fin >> pat;
        cout << "case " << icase << " pat " << pat << endl;

        /* solve case */
        ostringstream answer;
        answer << analyse(accel, dict, "", pat);

        /* store solution */
        fout << "Case #" << icase << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

    return 0;
}
