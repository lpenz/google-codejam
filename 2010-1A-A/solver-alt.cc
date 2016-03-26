/*
 * Compilation:
 * gcc -Wall -Werror -W -std=c++11 <file>.cpp
 *
 * Usage:
 * ./a.out <input file> <output file>
 */

#include <string.h>
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

typedef pair<int, int> lc_t;
typedef map<lc_t, char> Grid;

void grid_print(int N, const Grid& grid)
{
    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            lc_t lc(l, c);
            Grid::const_iterator p = grid.find(lc);
            if (p == grid.end()) {
                cout << '.';
                continue;
            }
            cout << p->second;
        }
        cout << endl;
    }
    cout << endl;
}

void count(const Grid& g, int* r, int* b)
{
    *r = 0;
    *b = 0;
    for (auto it : g) {
        if (it.second == 'R')
            *r += 1;
        if (it.second == 'B')
            *r += 1;
    }
}

extern inline void check(int K, char side, char cell, int* counter, bool* won, string msg __attribute__((unused)), int l __attribute__((unused)), int c __attribute__((unused)))
{
    if (*won)
        return;
    if (cell == side)
        *counter += 1;
    else
        *counter = 0;
    if (*counter >= K) {
        // cout << side << " won at " << msg << " " << l << " " << c << endl;
        *won = true;
    }
}

bool winner_side(int N __attribute__((unused)), int K, const Grid& grid, char c)
{
    for (auto it : grid) {
        /* horizontal */
        for (int k = 0; k < K; k++) {
            Grid::const_iterator i = grid.find(lc_t(it.first.first, it.first.second + k));
            if (i == grid.end() || i->second != c)
                break;
            if (k == K - 1) {
                cout << c << " - " << it.first.first << " " << it.first.second << endl;
                return true;
            }
        }
        /* vertical */
        for (int k = 0; k < K; k++) {
            Grid::const_iterator i = grid.find(lc_t(it.first.first + k, it.first.second));
            if (i == grid.end() || i->second != c)
                break;
            if (k == K - 1) {
                cout << c << " | " << it.first.first << " " << it.first.second << endl;
                return true;
            }
        }
        /* \ */
        for (int k = 0; k < K; k++) {
            Grid::const_iterator i = grid.find(lc_t(it.first.first + k, it.first.second + k));
            if (i == grid.end() || i->second != c)
                break;
            if (k == K - 1) {
                cout << c << " \\ " << it.first.first << " " << it.first.second << endl;
                return true;
            }
        }
        /* / */
        for (int k = 0; k < K; k++) {
            Grid::const_iterator i = grid.find(lc_t(it.first.first + k, it.first.second - k));
            if (i == grid.end() || i->second != c)
                break;
            if (k == K - 1) {
                cout << c << " / " << it.first.first << " " << it.first.second << endl;
                return true;
            }
        }
    }
    return false;
}

void winner(int N __attribute__((unused)), int K, const Grid& grid, bool* r, bool* b)
{
    *r = winner_side(N, K, grid, 'R');
    *b = winner_side(N, K, grid, 'B');
}

Grid rotate(int N, const Grid& grid)
{
    Grid grot;
    int r0;
    int b0;
    count(grid, &r0, &b0);
    for (auto& it : grid) {
        const lc_t& lc = it.first;
        lc_t lcr(lc.second, N - lc.first - 1);
        grot[lcr] = it.second;
    }
    int r1;
    int b1;
    count(grid, &r1, &b1);
    if (r0 != r1 || b0 != b1) {
        cerr << "error in count!" << endl;
        abort();
    }
    return grot;
}

Grid gravity(int N, const Grid& grid)
{
    Grid grav;
    int r0;
    int b0;
    count(grid, &r0, &b0);
    for (int c = 0; c < N; c++) {
        int fall = 0;
        for (int l = N - 1; l >= 0; l--) {
            lc_t lc(l, c);
            Grid::const_iterator p = grid.find(lc);
            if (p == grid.end()) {
                fall++;
                continue;
            }
            grav[lc_t(l + fall, c)] = p->second;
        }
    }
    int r1;
    int b1;
    count(grid, &r1, &b1);
    if (r0 != r1 || b0 != b1) {
        cerr << "error in count!" << endl;
        abort();
    }
    return grav;
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
        cout << "case " << icase << endl;
        /* read case */
        int N, K;
        fin >> N >> K;
        Grid grid;
        for (int l = 0; l < N; l++) {
            string line;
            fin >> line;
            int c = 0;
            for (auto& e : line) {
                if (e == '.') {
                    c++;
                    continue;
                }
                lc_t lc(l, c);
                grid[lc] = e;
                c++;
            }
        }
        // cout << "orig:" << endl;
        //grid_print(N, grid);

        /* solve case */

        /* rotate */
        // cout << "rot:" << endl;
        Grid grot = rotate(N, grid);
        //grid_print(N, grot);

        /* gravity */
        // cout << "grav:" << endl;
        Grid grav = gravity(N, grot);
        //grid_print(N, grav);

        string answer;
        /* winner */
        bool r = false;
        bool b = false;
        winner(N, K, grav, &r, &b);
        if (r && b)
            answer.assign("Both");
        else if (r)
            answer.assign("Red");
        else if (b)
            answer.assign("Blue");
        else
            answer.assign("Neither");

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
