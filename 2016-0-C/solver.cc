/*
 * Compilation:
 * gcc -Wall -Werror -W -std=c++11 <file>.cc -lgmpxx -lgmp
 *
 * This program uses the GNU multiple precision arithmetic library
 * (https://gmplib.org/)
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
#include <gmpxx.h>

using namespace std;

#include "primes.inc"

/* from https://www.topcoder.com/community/data-science/data-science-tutorials/primality-testing-non-deterministic-algorithms/ */
/* adapted to use gmp */
struct PrimalityTester_t {
    PrimalityTester_t()
    {
        gmp_randinit_default(randstate_);
    }

    /* This function calculates (ab)%c */
    mpz_class modulo(mpz_class a, mpz_class b, mpz_class c)
    {
        mpz_class x = 1;
        mpz_class y = a;
        while (b > 0) {
            if (b % 2 == 1) {
                x = (x * y) % c;
            }
            y = (y * y) % c; // squaring the base
            b /= 2;
        }
        return x % c;
    }

    /* this function calculates (a*b)%c taking into account that a*b might overflow */
    mpz_class mulmod(mpz_class a, mpz_class b, mpz_class c)
    {
        mpz_class x = 0;
        mpz_class y = a % c;
        while (b > 0) {
            if (b % 2 == 1) {
                x = (x + y) % c;
            }
            y = (y * 2) % c;
            b /= 2;
        }
        return x % c;
    }

    bool isprime(mpz_class val)
    {
        if (val < 2) {
            return false;
        }
        if (val != 2 && val % 2 == 0) {
            return false;
        }
        mpz_class s = val - 1;
        while (s % 2 == 0) {
            s /= 2;
        }
        for (int i = 0; i < iteration_; i++) {
            mpz_t a0;
            mpz_init(a0);
            mpz_class v1(val - 1);
            mpz_urandomm(a0, randstate_, v1.get_mpz_t());
            mpz_class a(a0);
            a++;
            mpz_class temp = s;
            mpz_class mod = modulo(a, temp, val);
            while (temp != val - 1 && mod != 1 && mod != val - 1) {
                mod = mulmod(mod, mod, val);
                temp *= 2;
            }
            if (mod != val - 1 && temp % 2 == 0) {
                return false;
            }
        }
        return true;
    }

    const int iteration_ = 20;
    gmp_randstate_t randstate_;
} PrimalityTester;

struct Solver {
    Solver(int N)
        : N_(N)
    {
        for (int base = 2; base <= 10; base++) {
            bv_.push_back(1 + pow(base, N_ - 1));
        }
        max_ = pow(2, N_) - 1;
    }

    void incr()
    {
        for (int i = 0; i < 9; i++) {
            int base = i + 2;
            // convert to bin representation:
            mpz_class bin;
            bin.set_str(bv_[i].get_str(base), 2);
            // always add base (2 for bin)
            bin += 2;
            if (i == 0 && bin > max_)
                throw;
            // parse back to base:
            bv_[i].set_str(bin.get_str(2), base);
        }
    }

    void fixJ()
    {
        while (hasprime())
            incr();
    }

    void incrJ()
    {
        incr();
        fixJ();
    }

    bool hasprime()
    {
        for (int i = 0; i < 9; i++) {
            if (PrimalityTester.isprime(bv_[i]))
                return true;
        }
        divisors_calc();
        return find(divisors_.begin(), divisors_.end(), 0) != divisors_.end();
    }

    void divisors_calc()
    {
        vector<int> r(9);
        for (auto p = 1U; p < Primes.size(); p++) {
            bool done = true;
            for (int i = 0; i < 9; i++) {
                if (r[i] == 0 && bv_[i] != Primes[p] && bv_[i] % Primes[p] == 0)
                    r[i] = Primes[p];
                if (r[i] == 0)
                    done = false;
            }
            if (done)
                break;
        }
        divisors_.assign(r.begin(), r.end());
    }

    string tostr()
    {
        ostringstream o;
        o << bv_[0].get_str(2);
        for (auto i : divisors_)
            o << " " << i;
        return o.str();
    }

    string debug()
    {
        ostringstream o;
        o << "N " << N_ << ": ";
        o << bv_[0].get_str(2);
        for (int i = 0; i < 9; i++) {
            int base = i + 2;
            mpz_class d(divisors_[i]);
            mpz_class e(bv_[i] / divisors_[i]);
            mpz_class r(bv_[i] % divisors_[i]);
            o << " ["
              << base
              << "~" << bv_[i]
              << "=" << d;
            o << "*" << e;
            o << "+" << r;
            o << "]";
        }
        return o.str();
    }

    int N_;
    mpz_class max_;
    vector<mpz_class> bv_;
    vector<mpz_class> divisors_;
};

int
do_main(int argc, char* argv[])
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
        int N, J;
        fin >> N >> J;

        /* solve case */
        fout << "Case #" << icase << ":" << endl;
        cout << "Case #" << icase << ": N " << N << ", J " << J << endl;
        Solver s(N);
        s.fixJ();
        for (int j = 0; j < J; j++) {
            cout << "  j " << j + 1 << "/" << J;
            cout << ": " << s.debug() << endl;
            fout << s.tostr() << endl;
            s.incrJ();
        }
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
