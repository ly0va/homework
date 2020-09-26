// Fib.hpp

#ifndef _FIB_HPP_
#define _FIB_HPP_

template <int N>
struct Fib {

    unsigned long f[N];
    unsigned long m;

    Fib(unsigned long newm=2) {
        reset(newm);
    }

    unsigned long next() {
       unsigned long sum = f[0];
       for (int i = 0; i < N-1; i++) {
           f[i] = f[i+1];
           sum = (sum + f[i+1]) % m;
       }
       return f[N-1] = sum % m;
    }

    void reset(unsigned long newm=2) {
        m = newm;
        for (int i = 0; i < N-1; i++)
            f[i] = 0;
        f[N-1] = 1;
    }
};

#endif
