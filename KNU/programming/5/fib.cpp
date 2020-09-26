// fib.cpp

#include "fib.hpp"

Fib::Fib(unsigned newm) {
    reset(newm);
}

unsigned Fib::next() {
   unsigned tmp = f[0];
   f[0] = f[1];
   f[1] = f[2];
   f[2] = (tmp + f[0] + f[1]) % m;
   return tmp;
}

void Fib::reset(unsigned newm) {
    m = newm;
    f[0] = f[1] = f[2] = 1;
}

