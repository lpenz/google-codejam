/*
 * Compilation:
 * gcc <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>


using namespace std;


int main(int argc, char *argv[])
{
	assert(argc == 3);

	/* open and read file passed as first command-line argument */
    ifstream fin (argv[1], fstream::in);

    /* open output file */
    ostringstream sout;
    sout << argv[2] << ".tmp";
    ofstream fout(sout.str().c_str(), fstream::out);

    /* read number of cases */
    int T;
    fin >> T;

    for (int c = 1; c <= T; c++) {
        /* read case */
        int N, L;
        fin >> N >> L;
        vector<string> iflow(N);
        vector<string> dflow(N);
        for (int i = 0; i < N; i++)
            fin >> iflow[i];
        for (int i = 0; i < N; i++)
            fin >> dflow[i];

        /* solve case */
        ostringstream answer("NOT POSSIBLE");

        /* store solution */
        fout << "Case #"<< c << ": " << answer.str() << endl;
    }

    fout.close();
    rename(sout.str().c_str(), argv[2]);

	return 0;
}

