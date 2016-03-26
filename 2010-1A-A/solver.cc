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

void winner(int N, int K, const Grid& grid, bool* r, bool* b)
{
    string rstr = string(K, 'R');
    string bstr = string(K, 'B');
    *r = false;
    *b = false;
    /* full grid */
    char gfull[N][N];
    for (int l = 0; l < N; l++)
        for (int c = 0; c < N; c++)
            gfull[l][c] = '.';
    for (auto it : grid)
        gfull[it.first.first][it.first.second] = it.second;
    /* horizontal */
    int rcounter;
    int bcounter;
    for (int l = 0; l < N; l++) {
        rcounter = 0;
        bcounter = 0;
        for (int c = 0; c < N; c++) {
            check(K, 'R', gfull[l][c], &rcounter, r, "-", l, c);
            check(K, 'B', gfull[l][c], &bcounter, b, "-", l, c);
        }
    }
    /* vertical */
    for (int c = 0; c < N; c++) {
        rcounter = 0;
        bcounter = 0;
        for (int l = 0; l < N; l++) {
            check(K, 'R', gfull[l][c], &rcounter, r, "|", l, c);
            check(K, 'B', gfull[l][c], &bcounter, b, "|", l, c);
        }
    }
    /* \ */
    for (int l = N - K; l >= 0; l--) {
        rcounter = 0;
        bcounter = 0;
        for (int c = 0; c < N - l; c++) {
            check(K, 'R', gfull[l + c][c], &rcounter, r, "\\", l + c, c);
            check(K, 'B', gfull[l + c][c], &bcounter, b, "\\", l + c, c);
        }
    }
    for (int c = 1; c <= N - K; c++) {
        rcounter = 0;
        bcounter = 0;
        for (int l = 0; l < N - c; l++) {
            check(K, 'R', gfull[l][c + l], &rcounter, r, "\\", l, c + l);
            check(K, 'B', gfull[l][c + l], &bcounter, b, "\\", l, c + l);
        }
    }
    /* / */
    for (int l = N - 1; l >= K; l--) {
        rcounter = 0;
        bcounter = 0;
        for (int c = 0; c <= l; c++) {
            // cout << "a " << l - c << " " << c << endl;
            check(K, 'R', gfull[l - c][c], &rcounter, r, "/", l - c, c);
            check(K, 'B', gfull[l - c][c], &bcounter, b, "/", l - c, c);
        }
    }
    for (int c = 1; c <= N - K; c++) {
        rcounter = 0;
        bcounter = 0;
        for (int l = N - 1; l >= c; l--) {
            // cout << "b " << l << " " << c + N - l - 1 << endl;
            check(K, 'R', gfull[l][c + N - l - 1], &rcounter, r, "/", l, c + N - l);
            check(K, 'B', gfull[l][c + N - l - 1], &bcounter, b, "/", l, c + N - l);
        }
    }
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
